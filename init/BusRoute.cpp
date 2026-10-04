#include "BusRoute.h"

BusRoute::BusRoute(string routeId)
    : routeId(routeId), outboundCount(0), built(false) {}

string BusRoute::getId() const {
    return routeId;
}

bool BusRoute::isBuilt() const {
    return built;
}

int BusRoute::getStopCount(Direction direction) {
    // TODO Q3
    if(!built) return 0;
    if(direction==OUTBOUND){
        return outboundCount;
    }
    return stops.size()-outboundCount+2;
}

int BusRoute::physicalIndex(int index, Direction direction) {
    // TODO Q3
    if(!built||index<0||index>=getStopCount(direction)){
        throw std::out_of_range("Index is out of range");
    }
    if(direction==OUTBOUND){
        return index;
    }
    return (outboundCount-1+index)%stops.size();
}

BusStop& BusRoute::getStop(int index, Direction direction) {
    // TODO Q3
    return stops.get(physicalIndex(index,direction));
}

void BusRoute::build(SLinkedList<BusStop>& outbound, SLinkedList<BusStop>& inbound) {
    // TODO Q3
    stops.clear();
    outboundCount=outbound.size();
    for(int i=0;i<outboundCount;i++){
        stops.add(outbound.get(i));
    }
    for(int i=1;i<outboundCount-1;i++){
        stops.add(inbound.get(i));
    }
    built=true;   
}

int BusRoute::getHopCount(string fromStopId, string toStopId, Direction direction) {
    // TODO Q3
    int fromindex=-1;
    int toindex=-1;
    for(int i=0;i<getStopCount(direction);i++){
        string id=getStop(i,direction).getId();
        if(id==fromStopId) fromindex=i;
        if(id==toStopId) toindex=i;
    }
    if(fromindex==-1||toindex==-1){
        return -1;
    }
    if(fromindex<toindex){
        return toindex-fromindex;
    }
    if(fromindex==toindex){
        return 0;
    }
    return -1;
}
