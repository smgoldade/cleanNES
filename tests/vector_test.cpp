#include <gtest/gtest.h>
#include "../src/vector.h"
#include "../src/vector.tpp"

TEST(vec2, FromAngle) {
    vec2f a = vec2f::from_angle(0.92729521f);
    vec2f b = {3.0f / 5.0f, 4.0f / 5.0f};
    vec2f c = vec2f::from_angle(7.2104805f);

    EXPECT_FLOAT_EQ(a.x, b.x) << "from_angle incorrect.";
    EXPECT_FLOAT_EQ(a.y, b.y) << "from_angle incorrect.";
    EXPECT_FLOAT_EQ(c.x, b.x) << "from_angle incorrect.";
    EXPECT_FLOAT_EQ(c.y, b.y) << "from_angle incorrect.";
}

TEST(vec2, Equality) {
    vec2i a = {1, 2};
    vec2i b = {-1, 2};
    vec2i c = {-1, 2};

    vec2f d = {1.0f, 2.0f};
    vec2f e = {-1.0f, 2.0f};
    vec2f f = {-1.0f, 2.0f};

    EXPECT_FALSE(a == b) << "(a == b) Equal failed.";
    EXPECT_FALSE(b == a) << "(b == a) Equal failed.";
    EXPECT_FALSE(a == c) << "(a == b) Equal failed.";
    EXPECT_FALSE(c == a) << "(b == a) Equal failed.";
    EXPECT_TRUE(b == c) << "(b == c) Equal failed.";
    EXPECT_TRUE(c == b) << "(c == b) Equal failed.";

    EXPECT_TRUE(a != b) << "(a != b) Not Equal failed.";
    EXPECT_TRUE(b != a) << "(b != a) Not Equal failed.";
    EXPECT_TRUE(a != c) << "(a != b) Not Equal failed.";
    EXPECT_TRUE(c != a) << "(b != a) Not Equal failed.";
    EXPECT_FALSE(b != c) << "(b != c) Not Equal failed.";
    EXPECT_FALSE(c != b) << "(c != b) Not Equal failed.";

    EXPECT_FALSE(d == e) << "(d == e) Equal failed.";
    EXPECT_FALSE(e == d) << "(e == d) Equal failed.";
    EXPECT_FALSE(d == f) << "(d == f) Equal failed.";
    EXPECT_FALSE(f == d) << "(f == d) Equal failed.";
    EXPECT_TRUE(e == f) << "(e == f) Equal failed.";
    EXPECT_TRUE(f == e) << "(f == e) Equal failed.";

    EXPECT_TRUE(d != e) << "(d != e) Not Equal failed.";
    EXPECT_TRUE(e != d) << "(e != d) Not Equal failed.";
    EXPECT_TRUE(d != f) << "(d != f) Not Equal failed.";
    EXPECT_TRUE(f != d) << "(f != d) Not Equal failed.";
    EXPECT_FALSE(e != f) << "(e != f) Not Equal failed.";
    EXPECT_FALSE(f != e) << "(f != e) Not Equal failed.";
}

TEST(vec2, Addition) {
    vec2i a = {1, 2};
    vec2i b = {-1, 2};

    auto c = a + b;
    EXPECT_EQ(a, vec2i(1, 2)) << "(V + V) Addition mutated LHS.";
    EXPECT_EQ(b, vec2i(-1, 2)) << "(V + V) Addition mutated RHS.";
    EXPECT_EQ(c, vec2i(0, 4)) << "(V + V) Addition failed.";

    a += b;
    EXPECT_EQ(a, vec2i(0, 4)) << "(V += V) Addition failed.";
    EXPECT_EQ(b, vec2i(-1, 2)) << "(V += V) Addition mutated RHS.";
}

TEST(vec2, Subtraction) {
    vec2i a = {1, 2};
    vec2i b = {-1, 2};

    auto c = a - b;
    EXPECT_EQ(a, vec2i(1, 2)) << "(V - V) Subtraction mutated LHS.";
    EXPECT_EQ(b, vec2i(-1, 2)) << "(V - V) Subtraction mutated RHS.";
    EXPECT_EQ(c, vec2i(2, 0)) << "(V - V) Subtraction failed.";

    a -= b;
    EXPECT_EQ(a, vec2i(2, 0)) << "(V -= V) Subtraction failed.";
    EXPECT_EQ(b, vec2i(-1, 2)) << "(V -= V) Subtraction mutated RHS.";
}

TEST(vec2, Negation) {
    vec2i a = {1, 2};

    auto b = -a;
    EXPECT_EQ(a, vec2i(1, 2)) << "Negation mutated LHS.";
    EXPECT_EQ(b, vec2i(-1, -2)) << "Negation failed.";
}

TEST(vec2, ScalarMultiplication) {
    vec2i a = {1, 2};
    int b = 4;

    auto c = a * b;
    EXPECT_EQ(a, vec2i(1, 2)) << "(V * s) Scalar multiplication mutated LHS.";
    EXPECT_EQ(b, 4) << "(V * s) Scalar multiplication mutated RHS.";
    EXPECT_EQ(c, vec2i(4, 8)) << "(V * s) Scalar multiplication failed.";

    auto d = b * a;
    EXPECT_EQ(a, vec2i(1, 2)) << "(s * V) Scalar multiplication mutated RHS.";
    EXPECT_EQ(b, 4) << "(s*V) Scalar multiplication mutated LHS.";
    EXPECT_EQ(d, vec2i(4, 8)) << "(s * V) Scalar multiplication failed.";

    a *= b;
    EXPECT_EQ(a, vec2i(4, 8)) << "(V *= s) Scalar multiplication failed.";
    EXPECT_EQ(b, 4) << "(V *= s) Scalar multiplication mutated RHS.";
}

TEST(vec2, ScalarDivision) {
    vec2i a = {4, 8};
    int b = 4;

    auto c = a / b;
    EXPECT_EQ(a, vec2i(4, 8)) << "(V / s) Scalar division mutated LHS.";
    EXPECT_EQ(b, 4) << "(V / s) Scalar division mutated RHS.";
    EXPECT_EQ(c, vec2i(1, 2)) << "(V / s) Scalar division failed.";

    a /= b;
    EXPECT_EQ(a, vec2i(1, 2)) << "(V /= s) Scalar division failed.";
    EXPECT_EQ(b, 4) << "(V /= s) Scalar division mutated RHS.";
}

TEST(vec2, DotProduct) {
    vec2i a = {1, 0};
    vec2i b = {0, 1};
    vec2i c = {2, 0};
    vec2i d = {2, 3};
    vec2i e = {4, 5};

    EXPECT_EQ(a.dot(b), 0) << "(a dot b) Dot product incorrect for orthogonal vectors.";
    EXPECT_EQ(a, vec2i(1, 0)) << "(a dot b) Dot product modified LHS.";
    EXPECT_EQ(b, vec2i(0, 1)) << "(a dot b) Dot product modified RHS.";
    EXPECT_EQ(b.dot(a), 0) << "(b dot a) Dot product incorrect for orthogonal vectors.";
    EXPECT_EQ(a, vec2i(1, 0)) << "(b dot a) Dot product modified RHS.";
    EXPECT_EQ(b, vec2i(0, 1)) << "(b dot a) Dot product modified LHS.";
    EXPECT_EQ(b.dot(c), 0) << "(b dot c) Dot product incorrect for orthogonal vectors.";
    EXPECT_EQ(c.dot(b), 0) << "(c dot b) Dot product incorrect for orthogonal vectors.";
    EXPECT_EQ(a.dot(c), 2) << "(a dot c) Dot product incorrect.";
    EXPECT_EQ(d.dot(e), 23) << "(d dot e) Dot product incorrect.";
}

TEST(vec2, SquareMagnitude) {
    vec2i a = {3, 4};
    vec2i b = {5, 7};
    vec2f c = {3.0f, 4.0f};
    vec2f d = {5.0f, 7.0f};

    EXPECT_EQ(a.square_magnitude(), 25) << "(a.square_magnitude) Square Magnitude incorrect.";
    EXPECT_EQ(a, vec2i(3, 4)) << "(a.square_magnitude) Vector modified by square magnitude call.";
// integer rounding
    EXPECT_EQ(b.square_magnitude(), 74) << "(b.square_magnitude) Square Magnitude incorrect.";
    EXPECT_EQ(b, vec2i(5, 7)) << "(b.square_magnitude) Vector modified by square magnitude call.";

    EXPECT_FLOAT_EQ(c.square_magnitude(), 25.0f) << "(c.square_magnitude) Square Magnitude incorrect.";
    EXPECT_EQ(c, vec2f(3.0f, 4.0f)) << "(c.square_magnitude) Vector modified by square magnitude call.";

    EXPECT_FLOAT_EQ(d.square_magnitude(), 74.0f) << "(d.square_magnitude) Square Magnitude incorrect.";
    EXPECT_EQ(d, vec2f(5.0f, 7.0f)) << "(d.square_magnitude) Vector modified by square magnitude call.";
}

TEST(vec2, Magnitude) {
    vec2i a = {3, 4};
    vec2i b = {5, 7};
    vec2f c = {3.0f, 4.0f};
    vec2f d = {5.0f, 7.0f};

    EXPECT_EQ(a.magnitude(), 5) << "(a.magnitude) Magnitude incorrect.";
    EXPECT_EQ(a, vec2i(3, 4)) << "(a.magnitude) Vector modified by magnitude call.";
// integer rounding
    EXPECT_EQ(b.magnitude(), 8) << "(b.magnitude) Magnitude incorrect.";
    EXPECT_EQ(b, vec2i(5, 7)) << "(b.magnitude) Vector modified by magnitude call.";

    EXPECT_FLOAT_EQ(c.magnitude(), 5.0f) << "(c.magnitude) Magnitude incorrect.";
    EXPECT_EQ(c, vec2f(3.0f, 4.0f)) << "(c.magnitude) Vector modified by magnitude call.";

    EXPECT_FLOAT_EQ(d.magnitude(), 8.602325439453125f) << "(d.magnitude) Magnitude incorrect.";
    EXPECT_EQ(d, vec2f(5.0f, 7.0f)) << "(d.magnitude) Vector modified by magnitude call.";
}

TEST(vec2, Angle) {
    vec2f a = {3.0f, 4.0f};
    vec2f b = {-3.0f, 4.0f};
    vec2f c = {-3.0f, -4.0f};
    vec2f d = {3.0f, -4.0f};

    EXPECT_FLOAT_EQ(a.angle(), 0.92729521f) << "(a.angle) Angle incorrect.";
    EXPECT_EQ(a, vec2f(3.0f, 4.0f)) << "(a.angle) Vector modified by angle call.";

    EXPECT_FLOAT_EQ(b.angle(), 2.2142975f) << "(b.angle) Angle incorrect.";
    EXPECT_EQ(b, vec2f(-3.0f, 4.0f)) << "(b.angle) Vector modified by angle call.";

    EXPECT_FLOAT_EQ(c.angle(), -2.2142975f) << "(c.angle) Angle incorrect.";
    EXPECT_EQ(c, vec2f(-3.0f, -4.0f)) << "(c.angle) Vector modified by angle call.";

    EXPECT_FLOAT_EQ(d.angle(), -0.92729521f) << "(d.angle) Angle incorrect.";
    EXPECT_EQ(d, vec2f(3.0f, -4.0f)) << "(d.angle) Vector modified by angle call.";
}

TEST(vec2, Norm) {
    vec2f a = {3.0f, 4.0f};
    vec2f a_n = {3.0f / 5.0f, 4.0f / 5.0f};
    vec2i b = {3, 4};
    vec2i b_n = {0, 0};

    EXPECT_EQ(a.norm(), a_n) << "(a.norm) Norm incorrect";
    EXPECT_EQ(a, vec2f(3.0f, 4.0f)) << "(a.norm) Vector modified by norm call.";
    EXPECT_EQ(b.norm(), b_n) << "(b.norm) Norm incorrect";
    EXPECT_EQ(b, vec2i(3, 4)) << "(b.norm) Vector modified by norm call.";
}