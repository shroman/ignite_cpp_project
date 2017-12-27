#include <iostream>
#include <chrono>
#include <cstdlib>

#include "ignite/ignition.h"
#include "ignite/ignite_configuration.h"

#include "scanner.h"

using namespace std::chrono;

using namespace ignite;
using namespace cache;

using namespace records;

int main(int argc, char* argv[]) {
    IgniteConfiguration cfg;

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " records_numsss" << std::endl;
        return 1;
    }

    // Ignition::SetClientMode();
    cfg.springCfgPath = "records.xml";

    cfg.jvmOpts.push_back("-Xms512m");
    cfg.jvmOpts.push_back("-Xmx512m");

    // Start a node.
    Ignite grid = Ignition::Start(cfg);

    // Get cache instance.
    Cache<int, Record> cache = grid.GetOrCreateCache<int, Record>("records");

    // Feed cache.
    for (int i = 0; i < atoi(argv[1]); ++i)
    {
        Record rec(i, i%100);

        cache.Put(i, rec);
    }

//    for (int i = 0; i < 1000; ++i)
//         std::cout << "Got [key=" << i << ", val=" "]" << std::endl;

    IgniteBinding binding = grid.GetBinding();
        
    binding.RegisterComputeFunc<ScanPartitions>();

    // broadcast several times.
    auto time_all = 0;

    for (int i = 0; i < 10; i++) {
        high_resolution_clock::time_point t1 = high_resolution_clock::now();

        // Do compute on remote nodes.
        compute::Compute compute = grid.GetCompute();

        compute.Broadcast(ScanPartitions());

        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

        time_all += duration;
        
        std::cout << "Duration: " << duration << " ms." << std::endl;
    }

    std::cout << "Agv. duration: " << time_all / 10 << " ms." << std::endl;

    Ignition::StopAll(false);

    std::cout << "Done." << std::endl;

    return 0;
}
