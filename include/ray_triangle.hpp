#ifndef RAY_TRIANGLE_HPP
#define RAY_TRIANGLE_HPP
#include "structs.hpp"

std::optional<intersection> intersect(const ray &r, const triangle &t){
    using scalar = vec3::Scalar;
    intersection ret;
    vec3 edge1, edge2, edge3, tvec, pvec, qvec;
    scalar det, inv_det;
    edge1 = t.vertices[1] - t.vertices[0];
    edge2 = t.vertices[2] - t.vertices[0];
    pvec = r.d.cross(edge2);
    det = edge1.dot(pvec);
    if (det > EPSILON){
        tvec = r.o - t.vertices[0];
        ret.u = tvec.dot(pvec);
        if (ret.u < 0.0 || ret.u > det)
            return std::nullopt;
        qvec = tvec.cross(edge1);
        ret.v = r.d.dot(qvec);
        if (ret.v < 0.0 || ret.u + ret.v > det)
            return std::nullopt;
    }
    else if (det < -EPSILON){
        tvec = r.o - t.vertices[0];
        ret.u = tvec.dot(pvec);
        if (ret.u > 0.0 || ret.u < det)
            return std::nullopt;
        qvec = tvec.cross(edge1);
        ret.v = r.d.dot(qvec);
        if (ret.v > 0.0 || ret.u + ret.v < det)
            return std::nullopt;
    }
    else
        return std::nullopt;
    inv_det = scalar(1) / det;
    ret.t = edge2.dot(qvec) * inv_det;
    (ret.u) *= inv_det;
    (ret.v) *= inv_det;
    ret.p = r.o + r.d * ret.t;
    return ret;
}
/*
#define CROSS(dest, v1, v2)                  \
    dest[0] = v1[1] * v2[2] - v1[2] * v2[1]; \
    dest[1] = v1[2] * v2[0] - v1[0] * v2[2]; \
    dest[2] = v1[0] * v2[1] - v1[1] * v2[0];
#define DOT(v1, v2) (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])
#define SUB(dest, v1, v2)    \
    dest[0] = v1[0] - v2[0]; \
    dest[1] = v1[1] - v2[1]; \
    dest[2] = v1[2] - v2[2];

int intersect_triangle(double orig[3], double dir[3],
                       double vert0[3], double vert1[3], double vert2[3],
                       double *t, double *u, double *v)
{
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det, inv_det;

    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);

    CROSS(pvec, dir, edge2);

    det = DOT(edge1, pvec);

    if (det > -EPSILON && det < EPSILON)
        return 0;
    inv_det = 1.0 / det;

    SUB(tvec, orig, vert0);

    *u = DOT(tvec, pvec) * inv_det;
    if (*u < 0.0 || *u > 1.0)
        return 0;

    CROSS(qvec, tvec, edge1);

    *v = DOT(dir, qvec) * inv_det;
    if (*v < 0.0 || *u + *v > 1.0)
        return 0;

    *t = DOT(edge2, qvec) * inv_det;

    return 1;
}

int intersect_triangle1(double orig[3], double dir[3],
                        double vert0[3], double vert1[3], double vert2[3],
                        double *t, double *u, double *v)
{
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det, inv_det;

    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);

    CROSS(pvec, dir, edge2);

    det = DOT(edge1, pvec);

    if (det > EPSILON)
    {
        SUB(tvec, orig, vert0);

        *u = DOT(tvec, pvec);
        if (*u < 0.0 || *u > det)
            return 0;

        CROSS(qvec, tvec, edge1);

        *v = DOT(dir, qvec);
        if (*v < 0.0 || *u + *v > det)
            return 0;
    }
    else if (det < -EPSILON)
    {
        SUB(tvec, orig, vert0);

        *u = DOT(tvec, pvec);
        if (*u > 0.0 || *u < det)
            return 0;

        CROSS(qvec, tvec, edge1);

        *v = DOT(dir, qvec);
        if (*v > 0.0 || *u + *v < det)
            return 0;
    }
    else
        return 0;
    inv_det = 1.0 / det;

    *t = DOT(edge2, qvec) * inv_det;
    (*u) *= inv_det;
    (*v) *= inv_det;

    return 1;
}

int intersect_triangle2(double orig[3], double dir[3],
                        double vert0[3], double vert1[3], double vert2[3],
                        double *t, double *u, double *v)
{
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det, inv_det;

    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);

    CROSS(pvec, dir, edge2);

    det = DOT(edge1, pvec);

    SUB(tvec, orig, vert0);
    inv_det = 1.0 / det;

    if (det > EPSILON)
    {
        *u = DOT(tvec, pvec);
        if (*u < 0.0 || *u > det)
            return 0;

        CROSS(qvec, tvec, edge1);

        *v = DOT(dir, qvec);
        if (*v < 0.0 || *u + *v > det)
            return 0;
    }
    else if (det < -EPSILON)
    {
        *u = DOT(tvec, pvec);
        if (*u > 0.0 || *u < det)
            return 0;

        CROSS(qvec, tvec, edge1);

        *v = DOT(dir, qvec);
        if (*v > 0.0 || *u + *v < det)
            return 0;
    }
    else
        return 0;
    *t = DOT(edge2, qvec) * inv_det;
    (*u) *= inv_det;
    (*v) *= inv_det;

    return 1;
}

int intersect_triangle3(double orig[3], double dir[3],
                        double vert0[3], double vert1[3], double vert2[3],
                        double *t, double *u, double *v)
{
    double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    double det, inv_det;

    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);

    CROSS(pvec, dir, edge2);

    det = DOT(edge1, pvec);

    SUB(tvec, orig, vert0);
    inv_det = 1.0 / det;

    CROSS(qvec, tvec, edge1);

    if (det > EPSILON)
    {
        *u = DOT(tvec, pvec);
        if (*u < 0.0 || *u > det)
            return 0;

        *v = DOT(dir, qvec);
        if (*v < 0.0 || *u + *v > det)
            return 0;
    }
    else if (det < -EPSILON)
    {
        *u = DOT(tvec, pvec);
        if (*u > 0.0 || *u < det)
            return 0;

        *v = DOT(dir, qvec);
        if (*v > 0.0 || *u + *v < det)
            return 0;
    }
    else
        return 0;
    *t = DOT(edge2, qvec) * inv_det;
    (*u) *= inv_det;
    (*v) *= inv_det;

    return 1;
}
*/
#endif
