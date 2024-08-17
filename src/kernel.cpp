#include "kernel.h"
float_t lapl_pse(float3_t posi, float3_t posj, float_t hi)
{
    float_t xi = posi.x;
    float_t yi = posi.y;
    float_t zi = posi.z;

    float_t xj = posj.x;
    float_t yj = posj.y;
    float_t zj = posj.z;

    float_t xij = xi - xj;
    float_t yij = yi - yj;
    float_t zij = zi - zj;

    float_t xx = sqrt(xij * xij + yij * yij + zij * zij);
    if (xx<1.e-6)
    {
        return 0;
    }
    

    float_t h2 = hi * hi;
    float_t h4 = h2 * h2;
    float_t h5 = hi * h4;
    float_t w2_pse = +4. / (h5 * M_PI * sqrt(M_PI)) * exp(-xx * xx / (h2));

    return w2_pse;
}
