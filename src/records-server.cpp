#include <iostream>

#include "ignite/ignition.h"
#include "ignite/ignite_configuration.h"

#include "scanner.h"

using namespace ignite;

int main(int argc, char* argv[]) {
    IgniteConfiguration cfg;

    // cfg.springCfgPath = "server.xml";

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " path_to_config_xml" << std::endl;
        return 1;
    }

    cfg.springCfgPath = argv[1];

    // cfg.jvmOpts.push_back("-Xms512m");
    // cfg.jvmOpts.push_back("-Xmx512m");

    // Start a node.
    Ignite grid = Ignition::Start(cfg);

    IgniteBinding binding = grid.GetBinding();
        
    binding.RegisterComputeFunc<ScanPartitions>();

    ignite::impl::IgniteImpl *igniteImpl = ignite::impl::IgniteImpl::GetFromProxy(grid);
    if (igniteImpl){
        ignite::jni::java::JniContext* context = igniteImpl->GetContext();

        std::cout << "Started." << std::endl;

        if (context)
            context->DestroyJvm();
    }

    return 0;
}
