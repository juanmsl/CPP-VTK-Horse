#include "horse.hxx"

Horse::Horse() {
    shapes.push_back(this->createTorso());
    shapes.push_back(this->createFrontLeg( 1.2, 0.8, -1.3));
    shapes.push_back(this->createFrontLeg( 1.2, 0.8,  1.3));
    shapes.push_back(this->createBackLeg(-3.2, 0.6, -0.9));
    shapes.push_back(this->createBackLeg(-3.2, 0.6,  0.9));
    shapes.push_back(this->createHead( 2.6, -1.8, 0));

    this->build();
}

void Horse::build() {
    for(int i = 0; i < this->shapes.size() - 1; i++) {
        ImplicitUnion join(this->shapes[i], this->shapes[i + 1], UNION);
        this->shapes[i + 1] = join;
    }
    this->implicitSource = this->shapes.rbegin()->getImplicitSource();
}

ImplicitUnion Horse::createTorso() {
    PureSphere s1(-1.3,  0.0,  0.9, 0.8);
    s1.scale(1, 1, 1.1);
    PureSphere s2(-1.3,  0.0, -0.9, 0.8);
    s2.scale(1, 1, 1.1);
    PureSphere s3( 0.0, -0.3,  0.0, 1.6);
    s3.scale(0.7, 1, 1);
    PureSphere s4( 1.5,  0.0,  0.0, 1.2);
    PureSphere s5( 2.5,  0.3,  0.4, 0.5);
    s5.scale(1, 1, 0.9);
    PureSphere s6( 2.5,  0.3, -0.4, 0.5);
    s6.scale(1, 1, 0.9);

    ImplicitUnion u1(s1, s2, UNION);
    ImplicitUnion u2(u1, s3, UNION);
    ImplicitUnion u3(u2, s4, UNION);
    ImplicitUnion u4(u3, s5, UNION);
    ImplicitUnion u5(u4, s6, UNION);
    u5.scale(0.9, 1, 1);

    return u5;
}

ImplicitUnion Horse::createFrontLeg(const double x, const double y, const double z) {
    PureSphere s1( 0.0,  0.0,  0.0, 0.1);
    s1.scale(1, 0.6, 1);
    PureCone c1( 0.0, 0.0, 0.0, 50);
    c1.scale(1, 2, 2);
    c1.rotate(60, 0, 0, 1);
    c1.translate( 0.0,  1.2,  0.0);

    ImplicitUnion u1(s1, c1, INTERSECTION);

    PureSphere s2( 0.0,  0.0,  0.0, 0.1);
    s2.scale(1, 0.6, 1);
    PureCone c2( 0.0, 0.0, 0.0, 50);
    c2.scale(1, 2, 2);
    c2.rotate(85, 0, 0, 1);
    c2.translate( 0.0,  1.2,  0.0);

    ImplicitUnion u2(s2, c2, INTERSECTION);
    u2.scale(1.7, 0.9, 1.7);
    u2.translate(0, 2, 0);

    ImplicitUnion u3(u1, u2, UNION);

    PureSphere s3( 0.0,  0.0,  0.0, 0.01);
    s3.scale(3, 3, 3);
    PureSphere s4(-0.5,  0.0,  0.0, 0.05);
    s4.scale(2, 3, 3);

    ImplicitUnion u4(s3, s4, UNION);
    u4.translate(0, 4, 0);

    ImplicitUnion u5(u3, u4, UNION);

    u5.translate(x, y, z);

    return u5;
}

ImplicitUnion Horse::createBackLeg(const double x, const double y, const double z) {
    PureSphere s1( 0.0,  0.0,  0.0, 0.3);
    s1.scale(1, 0.6, 1);
    PureCone c1( 0.0, 0.0, 0.0, 55);
    c1.scale(1, 2, 2);
    c1.rotate(80, 0, 0, 1);
    c1.translate( 0.0,  1.4,  0.0);

    ImplicitUnion u1(s1, c1, INTERSECTION);

    PureSphere s2( 0.0,  0.0,  0.0, 0.3);
    s2.scale(1, 0.6, 1);
    PureCone c2( 0.0, 0.0, 0.0, 55);
    c2.scale(1, 2, 2);
    c2.rotate(85, 0, 0, 1);
    c2.translate( 0.0,  1.4,  0.0);

    ImplicitUnion u2(s2, c2, INTERSECTION);
    u2.scale(1.7, 0.9, 1.7);
    u2.translate(0, 2, 0);

    ImplicitUnion u3(u1, u2, UNION);

    PureSphere s3( 0.0,  0.0,  0.0, 0.01);
    s3.scale(3, 3, 3);
    PureSphere s4(-0.5,  0.0,  0.0, 0.05);
    s4.scale(2, 3, 3);

    ImplicitUnion u4(s3, s4, UNION);
    u4.translate(0, 4, 0);

    ImplicitUnion u5(u3, u4, UNION);

    u5.translate(x, y, z);

    return u5;
}

ImplicitUnion Horse::createHead(const double x, const double y, const double z) {

    // NECK
    PureSphere s1( 0.0,  0.0,  0.0, 1.4);
    PureCone c1( 0.0,  0.0,  0.0, 10);
    c1.scale(2, 1.5, 1.6);
    c1.translate(1.4, 0, 0);
    c1.rotate(45, 0, 0, 1);

    ImplicitUnion u1(s1, c1, INTERSECTION);

    // HEAD
    PureSphere s2( 0.0,  0.0,  0.0, 0.2);
    s2.scale(1, 1, 1.2);
    PureSphere s3(-0.2, -0.2, -0.3, 0.1);
    s3.scale(1.3, 1.3, 1.3);
    PureSphere s4(-0.2, -0.2,  0.3, 0.1);
    s4.scale(1.3, 1.3, 1.3);

    ImplicitUnion u2(s3, s4, UNION);
    ImplicitUnion u3(u2, s2, UNION);

    u3.translate(1.1, -0.5, 0.0);

    ImplicitUnion u4(u3, u1, UNION);

    // MOUTH
    PureSphere s5( 0.0,  0.0,  0.0, 0.5);
    PureCone c2( 0.0,  0.0,  0.0, 20);
    c2.scale(2, 1.5, 1.7);
    c2.translate(0.5, 0, 0);
    c2.rotate(-35, 0, 0, 1);

    ImplicitUnion u5(s5, c2, INTERSECTION);
    u5.translate(2.0,  0.0, 0);

    ImplicitUnion u6(u5, u4, UNION);

    // NOSE
    PureSphere s6( 0.0,  0.0, -0.8, 0.1);
    s6.scale(2.5, 2.5, 2.5);
    PureSphere s7( 0.0,  0.0,  0.8, 0.1);
    s7.scale(2.5, 2.5, 2.5);

    ImplicitUnion u7(s6, s7, UNION);
    u7.translate(2.7, 0.1, 0);

    ImplicitUnion u8(u7, u6, UNION);

    // EARS
    PureSphere s8( 0.0,  0.0,  0.0, 0.1);
    s8.scale(2.8, 1.5, 3.3);
    PureSphere s9( 0.0,  0.5,  0.0, 0.1);
    s9.scale(2.8, 1.5, 3.3);

    ImplicitUnion u9(s8, s9, UNION);
    u9.translate( 1.0, -1.5, -0.7);
    u9.scale(1.2, 1.2, 1.2);

    PureSphere s10( 0.0,  0.0,  0.0, 0.1);
    s10.scale(2.8, 1.5, 3.3);
    PureSphere s11( 0.0,  0.5,  0.0, 0.1);
    s11.scale(2.8, 1.5, 3.3);

    ImplicitUnion u10(s10, s11, UNION);
    u10.translate( 1.0, -1.5,  0.7);
    u10.scale(1.2, 1.2, 1.2);

    ImplicitUnion u11(u8, u9, UNION);
    ImplicitUnion u12(u10, u11, UNION);

    u12.translate(x, y, z);

    return u12;
}