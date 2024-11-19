#include <iostream>
#include <vector>
#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

// Define the state type (x, y) for the 2D vector field
typedef std::vector<double> state_type;

// Define the vector field as a system of ODEs
void vector_field(const state_type &r, state_type &drdt, double /* t */) {
    double x = r[0];
    double y = r[1];
    drdt[0] = -y; // dx/dt = u(x, y)
    drdt[1] = x;  // dy/dt = v(x, y)
}

int main() {
    // Initial condition for the streamline
    state_type r(2);       // State vector [x, y]
    r[0] = 1.0;            // x0
    r[1] = 0.0;            // y0

    // Integration parameters
    double t_start = 0.0;
    double t_end = 10.0;
    double dt = 0.02;

    // Run the integration with a simple Runge-Kutta 4 stepper
    runge_kutta4<state_type> stepper;

    // Use a lambda function to print each state (x, y) to the console
    integrate_const(stepper, vector_field, r, t_start, t_end, dt, 
        [](const state_type &r, double  t) {
            cout << "t = " << t <<" x: " << r[0] << ", y: " << r[1] << endl;
        });

    return 0;
}
