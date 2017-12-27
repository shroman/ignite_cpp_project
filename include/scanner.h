#include <thread>
// #include <future>
#include <iostream>
#include <vector>

#include "ignite/ignite.h"

#include "record.h"

using namespace ignite;
using namespace ignite::cache;
using namespace ignite::cache::query;

using namespace pushpf;

class ScanPartitions : public compute::ComputeFunc<void>
{
    friend struct ignite::binary::BinaryType<ScanPartitions>;
public:
    ScanPartitions() = default;
    ScanPartitions(const ScanPartitions&) = default;
    ScanPartitions& operator=(const ScanPartitions&) = default;

    virtual void Call()
    {
        try {
        // int all = 0;
        Ignite grid = Ignition::Get();

        Cache<int, Record> cache = grid.GetCache<int, Record>("pushpf");

        // iterate over partitions.
        // Ugh! Partition number is fixed here.
        // for (int i=0; i < 1024; i++){
        //     all += PartitionScan(cache, i);
        // }

        // multithreaded.
        // std::vector<std::thread> threads;

        // Very slow.
        // for (int i=0; i < 1024; i++){
        //     // std::thread t(task, i);
        //     std::thread t(PartitionScan, std::ref(cache), i);
        //     threads.push_back(std::move(t));
        // }

        // for (int i=0; i < threads.size(); i++){
        //     threads[i].join();
        // }

        /// Using futures. ///
        // std::vector<std::future<int>> futures;

        // // for (int i=0; i < 1024; i++){
        //     std::promise<int> p;
        //     futures.push_back(p.get_future());
        //     threads.push_back(std::thread(ScanP, std::ref(cache), std::move(p)));
        // // }

        // for (int i=0; i < futures.size(); i++){
        //     all += futures[i].get();
        // }

        // for (int i=0; i < threads.size(); i++){
        //     threads[i].join();
        // }
        
        std::cout << "Records found: " << PartitionScan(cache, 0) << std::endl;
    }
    catch (std::exception& e){
        std::cout << "Exception caught" << std::endl;
        std::cout << e.what() << std::endl;
    }
    }

private:
    static int PartitionScan(Cache<int, Record>& cache, int part) {
        // ScanQuery qry(part);
        ScanQuery qry;
        qry.SetLocal(true);

        QueryCursor<int, Record> cur = cache.Query(qry);

        std::vector<CacheEntry<int, Record>> res;
        cur.GetAll(res);

        // std::cout << "Found " << res.size() << " records." << std::endl;

        int size = 0;

        // kinda filter...
        if (res.size() > 0) {
            if (res[0].GetValue().id < 10) {
                Record rec(res[0].GetValue());
                std::cout << "  << " << rec.topicId << std::endl;
            }

            for (int i=0; i < res.size(); i++) {
                if (res[i].GetValue().flag == 1)
                    size++;
            }
        }

        return size;
    }
};

namespace ignite
{
    namespace binary
    {
        template<>
        struct BinaryType<ScanPartitions>
        {
            static int32_t GetTypeId()
            {
                return GetBinaryStringHashCode("ScanPartitions");
            }

            static void GetTypeName(std::string& dst)
            {
                dst = "ScanPartitions";
            }

            static int32_t GetFieldId(const char* name)
            {
                return GetBinaryStringHashCode(name);
            }

            static bool IsNull(const ScanPartitions& obj)
            {
                return false;
            }

            static void GetNull(ScanPartitions& dst)
            {
                dst = ScanPartitions();
            }

            static void Write(BinaryWriter& writer, const ScanPartitions& obj)
            {
                // writer.WriteObject<IgniteError>("err", obj.err);
            }

            static void Read(BinaryReader& reader, ScanPartitions& dst)
            {
                // dst.err = reader.ReadObject<IgniteError>("err");
            }
        };
    }
}
