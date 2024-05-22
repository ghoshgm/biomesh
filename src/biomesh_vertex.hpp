
#ifndef BIOMESH_VERTEX_HPP
#define BIOMESH_VERTEX_HPP

/**
 * @brief Class for cartesian coordinates.
 */
class vertex
{
public:
  /**
   * Default constructor.
   */
  vertex ();

  /**
   * Custom constructor.
   */
  vertex (double x, double y
#ifdef BIOMESH_ENABLE_3D
          ,
          double z
#endif
  );

  /**
   * Getter for co-ordinate in the X,Y,Z direction.
   */
  double operator() (char dir);

private:
  double m_x, m_y, m_z; /* Cartesian coordinates. */
};

#endif