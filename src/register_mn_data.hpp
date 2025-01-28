#pragma once // #ifndef beldex_transfer_utils_hpp

#include "cryptonote_tx_utils.h"
    
struct master_node_data{
		master_nodes::contributor_args_t contributor_args;
		uint64_t time_stamp;
        crypto::public_key master_node_key;
	    crypto::signature signature;
	};

    