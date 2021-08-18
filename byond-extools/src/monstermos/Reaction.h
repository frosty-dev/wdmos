#pragma once

#include "GasMixture.h"

#include "../core/core.h"

#include "../core/proc_management.h"

#include <unordered_map>

extern std::vector<Value> gas_id_to_type;

class Reaction
{
    public:
        bool check_conditions(const GasMixture& mix) const;
        int react(GasMixture& mix,Value src,Value holder) const;
        inline float get_priority() { return priority; }
        Reaction(Value v);
    private:
        Reaction();
        float reaction_id_hash;
        float priority;
        float min_temp_req = -1.0;
        float max_temp_req = 1e31;
        float min_ener_req = -1.0;
        std::unordered_map<unsigned int,float> min_gas_reqs;
        unsigned int proc_id;
};

extern std::vector<Reaction> cached_reactions; 