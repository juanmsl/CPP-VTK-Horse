#ifndef __HORSE_HXX__
#define __HORSE_HXX__

#include "shapes/shapes.hxx"
#include "shapes/booleanunion.hxx"
#include "shapes/implicitunion.hxx"

class Horse : public Shape {
    protected:
        std::vector<ImplicitUnion> shapes;

    public:
        Horse();

    private:
        void build();
        ImplicitUnion createTorso();
        ImplicitUnion createFrontLeg(const double x, const double y, const double z);
        ImplicitUnion createBackLeg(const double x, const double y, const double z);
        ImplicitUnion createLeg(const double x, const double y, const double z);
        ImplicitUnion createHead(const double x, const double y, const double z);
};

#endif
