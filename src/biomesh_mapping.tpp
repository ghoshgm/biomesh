
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
  double w0 = (1 - r) * (1 - s) * (1 - t);
  double w1 = r * (1 - s) * (1 - t);
  double w2 = r * s * (1 - t);
  double w3 = (1 - r) * s * (1 - t);
  double w4 = (1 - r) * (1 - s) * t;
  double w5 = r * t * (1 - s);
  double w6 = r * s * t;
  double w7 = (1 - r) * s * t;

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