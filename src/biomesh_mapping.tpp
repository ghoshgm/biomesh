
template <class vertex>
vertex
isoparametric (const vertex &parametric_coords,
               std::array<vertex, 8> &vertices)
{
  /* Parametric coordinates. */
  double r = parametric_coords ('x');
  double s = parametric_coords ('y');
  double t = parametric_coords ('z');

  /* Cartesian coordinates. */
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  /* Mapping weights. */
  double w0 = (1.0 - r) * (1.0 - s) * (1.0 - t);
  double w1 = r * (1.0 - s) * (1.0 - t);
  double w2 = r * s * (1 - t);
  double w3 = (1.0 - r) * s * (1.0 - t);
  double w4 = (1.0 - r) * (1.0 - s) * t;
  double w5 = r * t * (1.0 - s);
  double w6 = r * s * t;
  double w7 = (1.0 - r) * s * t;

  /* Compute cartesian coordinates. */
  x = (vertices[0]('x') * w0) + (vertices[1]('x') * w1)
      + (vertices[2]('x') * w2) + (vertices[3]('x') * w3)
      + (vertices[4]('x') * w4) + (vertices[5]('x') * w5)
      + (vertices[6]('x') * w6) + (vertices[7]('x') * w7);
  y = (vertices[0]('y') * w0) + (vertices[1]('y') * w1)
      + (vertices[2]('y') * w2) + (vertices[3]('y') * w3)
      + (vertices[4]('y') * w4) + (vertices[5]('y') * w5)
      + (vertices[6]('y') * w6) + (vertices[7]('y') * w7);
  z = (vertices[0]('z') * w0) + (vertices[1]('z') * w1)
      + (vertices[2]('z') * w2) + (vertices[3]('z') * w3)
      + (vertices[4]('z') * w4) + (vertices[5]('z') * w5)
      + (vertices[6]('z') * w6) + (vertices[7]('z') * w7);

  return vertex (x, y, z);
}

struct petsc_context
{
  std::array<double, 3> cv;
  Eigen::VectorXd xv;
  Eigen::VectorXd yv;
  Eigen::VectorXd zv;
};

static PetscErrorCode
FormFunction (SNES snes, Vec x, Vec f, void *ctx)
{
  petsc_context *pc = (petsc_context *)ctx;
  const PetscScalar *sol;
  PetscScalar *res;

  double cx = pc->cv[0];
  double cy = pc->cv[1];
  double cz = pc->cv[2];
  auto xv = pc->xv;
  auto yv = pc->yv;
  auto zv = pc->zv;
  VecGetArrayRead (x, &sol);
  VecGetArray (f, &res);

  res[0] = xv (0) + (xv (1) * sol[0]) + (xv (2) * sol[1]) + (xv (3) * sol[2])
           + (xv (4) * sol[0]) * (sol[1] + xv (5)) * (sol[0] * sol[2])
           + (xv (6) * sol[1] * sol[2]) + (xv (7) * sol[0] * sol[1] * sol[2])
           - cx;
  res[1] = yv (0) + (yv (1) * sol[0]) + (yv (2) * sol[1]) + (yv (3) * sol[2])
           + (yv (4) * sol[0] * sol[1]) + (yv (5) * sol[0] * sol[2])
           + (yv (6) * sol[1] * sol[2]) + (yv (7) * sol[0] * sol[1] * sol[2])
           - cy;
  res[2] = zv (0) + (zv (1) * sol[0]) + (zv (2) * sol[1]) + (zv (3) * sol[2])
           + (zv (4) * sol[0] * sol[1]) + (zv (5) * sol[0] * sol[2])
           + (zv (6) * sol[1] * sol[2]) + (zv (7) * sol[0] * sol[1] * sol[2])
           - cz;

  VecRestoreArrayRead (x, &sol);
  VecRestoreArray (f, &res);

  return 0;
}

static PetscErrorCode
FormJacobian (SNES snes, Vec x, Mat j, Mat P, void *ctx)
{
  petsc_context *pc = (petsc_context *)ctx;
  const PetscScalar *sol;
  PetscScalar jval[9];
  PetscInt row[3] = { 0, 1, 2 }, col[3] = { 0, 1, 2 };

  auto xv = pc->xv;
  auto yv = pc->yv;
  auto zv = pc->zv;

  VecGetArrayRead (x, &sol);

  /* Partial derivatives of the first equation. */
  jval[0] = xv (1) + (xv (4) * sol[1]) + (xv (5) * sol[2])
            + (xv (7) * sol[1] * sol[2]);
  jval[1] = xv (2) + (xv (4) * sol[0]) + (xv (6) * sol[2])
            + (xv (7) * sol[0] * sol[2]);
  jval[2] = xv (3) + (xv (5) * sol[0]) + (xv (6) * sol[1])
            + (xv (7) * sol[0] * sol[1]);

  /* Partial derivatives of the second equation. */
  jval[3] = yv (1) + (yv (4) * sol[1]) + (yv (5) * sol[2])
            + (yv (7) * sol[1] * sol[2]);
  jval[4] = yv (2) + (yv (4) * sol[0]) + (yv (6) * sol[2])
            + (yv (7) * sol[0] * sol[2]);
  jval[5] = yv (3) + (yv (5) * sol[0]) + (yv (6) * sol[1])
            + (yv (7) * sol[0] * sol[1]);

  /* Partial derivatives of the third equation. */
  jval[6] = zv (1) + (zv (4) * sol[1]) + (zv (5) * sol[2])
            + (zv (7) * sol[1] * sol[2]);
  jval[7] = zv (2) + (zv (4) * sol[0]) + (zv (6) * sol[2])
            + (zv (7) * sol[0] * sol[2]);
  jval[8] = zv (3) + (zv (5) * sol[0]) + (zv (6) * sol[1])
            + (zv (7) * sol[0] * sol[1]);

  MatSetValues (P, 3, row, 3, col, jval, INSERT_VALUES);
  VecRestoreArrayRead (x, &sol);
  MatAssemblyBegin (P, MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd (P, MAT_FINAL_ASSEMBLY);

  return 0;
}

template <class vertex>
vertex
inverse_isoparametric (const vertex &cartesian_coords,
                       std::array<vertex, 8> &vertices)
{
  /**
   * Assume bilinear mapping from the cartesian space to
   * parametric space.
   * This requires solving nonlinear equations.
   * Currently, PETSc is the only reliable solver written in C.
   */
  SNES snes;
  Vec sol;
  Mat jacobian;
  PetscErrorCode ierr;

  /* Compute the coefficients of the bilinear mapping. */
  Eigen::MatrixXd bmat{ { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                        { 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                        { 1.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0 },
                        { 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                        { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0 },
                        { 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0 },
                        { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
                        { 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0 } };

  Eigen::VectorXd xvec{ { vertices[0]('x'), vertices[1]('x'), vertices[2]('x'),
                          vertices[3]('x'), vertices[4]('x'), vertices[5]('x'),
                          vertices[6]('x'), vertices[7]('x') } };

  Eigen::VectorXd yvec{ { vertices[0]('y'), vertices[1]('y'), vertices[2]('y'),
                          vertices[3]('y'), vertices[4]('y'), vertices[5]('y'),
                          vertices[6]('y'), vertices[7]('y') } };

  Eigen::VectorXd zvec{ { vertices[0]('z'), vertices[1]('z'), vertices[2]('z'),
                          vertices[3]('z'), vertices[4]('z'), vertices[5]('z'),
                          vertices[6]('z'), vertices[7]('z') } };

  Eigen::VectorXd alpha = bmat.inverse () * xvec;
  Eigen::VectorXd beta = bmat.inverse () * yvec;
  Eigen::VectorXd gamma = bmat.inverse () * zvec;

  /* Setup context for PETSc solver. */
  petsc_context pc;
  pc.cv[0] = cartesian_coords ('x');
  pc.cv[1] = cartesian_coords ('y');
  pc.cv[2] = cartesian_coords ('z');
  pc.xv = alpha;
  pc.yv = beta;
  pc.zv = gamma;

  /* Allocate solution vector. */
  VecCreate (PETSC_COMM_SELF, &sol);
  VecSetSizes (sol, PETSC_DECIDE, 3);
  VecSetFromOptions (sol);
  ierr = VecSet (sol, (PetscScalar)0.0);
#if 0
  VecView (sol, PETSC_VIEWER_STDOUT_WORLD);
#endif

  /* Allocate Jacobian matrix. */
  MatCreate (PETSC_COMM_SELF, &jacobian);
  MatSetSizes (jacobian, PETSC_DECIDE, PETSC_DECIDE, 3, 3);
  MatSetFromOptions (jacobian);
  MatSetUp (jacobian);

  /* Allocate SNES solver. */
  SNESCreate (PETSC_COMM_SELF, &snes);
  SNESSetFunction (snes, NULL, FormFunction, &pc);
  SNESSetJacobian (snes, jacobian, jacobian, FormJacobian, &pc);
  SNESSetFromOptions (snes);

  /* Solve eqautions. */
  SNESSolve (snes, NULL, sol);
#if 0
  MatView (jacobian, PETSC_VIEWER_STDOUT_WORLD);
#endif

  /* Print solution. */
  PetscScalar *result;
  VecGetArray (sol, &result);
#if 0
  PetscPrintf(PETSC_COMM_SELF, "Solution: x = %f, y = %f, z = %f\n", result[0],result[1],result[2]);
#endif

  /* Free memory. */
  VecDestroy (&sol);
  MatDestroy (&jacobian);
  SNESDestroy (&snes);

  return vertex (result[0], result[1], result[2]);
}