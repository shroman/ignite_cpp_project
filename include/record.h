#ifndef _RECORD_
#define _RECORD_

#include <string>

#include "ignite/ignite.h"
#include "ignite/ignition.h"

namespace records {

    class Record {
        int id;

        int flag;

    public:
        Record(): id(0){}

        Record(int id, int flag): id(id), flag(flag){}
    };
}

namespace ignite {
    namespace binary {
        IGNITE_BINARY_TYPE_START(records::Record)

            typedef records::Record Record;
        
            IGNITE_BINARY_GET_TYPE_ID_AS_HASH(records::Record)
            IGNITE_BINARY_GET_TYPE_NAME_AS_IS(records::Record)
            IGNITE_BINARY_GET_FIELD_ID_AS_HASH
            IGNITE_BINARY_IS_NULL_FALSE(records::Record)
            IGNITE_BINARY_GET_NULL_DEFAULT_CTOR(records::Record)

            static void Write(BinaryWriter& writer, const records::Record& obj)
            {
                writer.WriteInt32("id", obj.id);
                writer.WriteInt32("flag", obj.flag);
            }

            static void Read(BinaryReader& reader, records::Record& dst)
            {
                dst.id = reader.ReadInt32("id");
                dst.flag = reader.ReadInt32("flag");
            }
        
        IGNITE_BINARY_TYPE_END
    }
}
#endif //_RECORD_
