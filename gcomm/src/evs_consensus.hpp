/*
 * Copyright (C) 2009 Codership Oy <info@codership.com>
 */

#include "evs_seqno.hpp"


namespace gcomm
{
    class UUID;
    class View;
    namespace evs
    {
        class NodeMap;
        class InputMap;
        class Message;
        class Consensus;
    }
}

class gcomm::evs::Consensus
{
public:   
    Consensus(const UUID& uuid_,
              const NodeMap& known_, 
              const InputMap& input_map_,
              const View& current_view_) :
        uuid(uuid_),
        known(known_),
        input_map(input_map_),
        current_view(current_view_)
    { }
    
    // Compares join message against current state
    
    bool is_consistent(const Message&) const;
    /*!
     * Compute highest reachable safe seq from local state
     *
     * @return Highest reachable safe seq
     */
    Seqno highest_reachable_safe_seq() const;
    /*!
     * Check if highest reachable safe seq according to message
     * consistent with local state.
     */
    bool is_consistent_highest_reachable_safe_seq(const Message&) const;
    /*!
     * Check if message aru seq, safe seq and node ranges matches to
     * local state.
     */
    bool is_consistent_input_map(const Message&) const;
    /*!
     * Check if message joining nodes match to local state.
     */
    bool is_consistent_joining(const Message&) const;
    bool is_consistent_partitioning(const Message&) const;
    bool is_consistent_leaving(const Message&) const;
    bool is_consistent_same_view(const Message&) const;
    bool is_consensus() const;    
private:

    const UUID& get_uuid() const { return uuid; }
    
    const UUID& uuid;
    const NodeMap& known;
    const InputMap& input_map;
    const View& current_view;
};