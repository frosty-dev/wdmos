#include "Reaction.h"

#include <algorithm>

using namespace monstermos::constants;

Reaction::Reaction(Value v)
{
    List min_reqs = v.get("min_requirements");
    if(min_reqs.at("TEMP").type == DataType::NUMBER) min_temp_req = min_reqs.at("TEMP");
    if(min_reqs.at("MAX_TEMP").type == DataType::NUMBER) max_temp_req = min_reqs.at("MAX_TEMP");
    if(min_reqs.at("ENER").type == DataType::NUMBER) min_ener_req = min_reqs.at("ENER");
    for(unsigned int i=0;i < TOTAL_NUM_GASES;i++)
    {
        auto gasReq = min_reqs.at(gas_id_to_type[i]);
        if(gasReq.type == DataType::NUMBER)
        {
            min_gas_reqs[i] = gasReq;
        }
    }
    priority = v.get("priority");
    auto proc = Core::try_get_proc(Core::stringify(v.get("type")) + "/react");
    if(!proc)
    {
        Core::alert_dd("ПРОЁБ-ПРОЁБ: " + Core::stringify(v.get("type")) + "/react");
    }
    else
    {
        Core::alert_dd("РЕАКЦИЯ: " + Core::stringify(v.get("type")) + "/react");
    }
    proc_id = proc->id;
}

bool Reaction::check_conditions(const GasMixture& air) const
{
    if(air.get_temperature() < min_temp_req || air.get_temperature() > max_temp_req || air.thermal_energy() < min_ener_req)
    {
        return false;
    }
    else
    {
        for(auto& info : min_gas_reqs)
        {
            if(air.get_moles(info.first) < info.second)
            {
                return false;
            }
        }
    }
    return true;
}

int Reaction::react(GasMixture& air,Value src,Value holder) const
{
    return (int)(float)(Core::get_proc(proc_id).call({src,holder}));
} 