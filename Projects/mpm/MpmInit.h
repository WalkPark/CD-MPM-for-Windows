#ifndef MPM_INIT_H
#define MPM_INIT_H

#include <Ziran/CS/Util/RandomNumber.h>
#include <Ziran/Math/Geometry/MeshConstruction.h>
#include <Ziran/Sim/MeshHandle.h>
#include <Ziran/Sim/SceneInitializationCore.h>
#include "MpmSimulation.h"
#include "MpmInit2D.h"
#include "MpmInit3D.h"

namespace ZIRAN {

template <class T, int dim>
class MpmInitBase {
public:
    using TV = Vector<T, dim>;
    using TVI = Vector<int, dim>;

    MpmSimulation<T, dim>& sim; // This contains the real scene data.
    SceneInitialization<T, dim> scene; // This stores a reference to the scene.
    MpmInitializationHelper<T, dim> init_helper;
    const int test_number;

    MpmInitBase(MpmSimulation<T, dim>& sim, const int test_number)
        : sim(sim)
        , scene(sim.scene)
        , init_helper(sim)
        , test_number(test_number)
    {
    }

    // Normal start call.
    void start()
    {
        printBasicInfo();
        initialize();
        sim.simulate();
    }

    // Restart call.
    void restart(int frame)
    {
        initialize();
        sim.restart(frame);
        sim.simulate();
    }

    void initialize()
    {
        reload();
        sim.initialize();
        sim.reinitialize();
    }

    virtual void reload() = 0;

    void printBasicInfo()
    {
        bool is_double = std::is_same<T, double>();
        //ZIRAN_INFO("Simulation using double:", is_double);
        //ZIRAN_INFO("Simulation dimension:", dim);
    }
};
} // namespace ZIRAN
#endif
