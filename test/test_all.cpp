//
//  test_all.cpp
//  MyMonero
//
//  Copyright (c) 2014-2019, MyMonero.com
//
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification, are
//  permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//	conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//	of conditions and the following disclaimer in the documentation and/or other
//	materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors may be
//	used to endorse or promote products derived from this software without specific
//	prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
//  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
//  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//
// Test module setup
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LibMoneroTests
#include <boost/test/unit_test.hpp> // last
//
// Includes & namespaces
#include <iostream>
#include <iterator>
#include <sstream>
using namespace std;
#include "epee/string_tools.h"
using namespace epee;
using namespace boost;
#include "cryptonote_format_utils.h"
#include <boost/property_tree/json_parser.hpp>
//
#include "beldex_fork_rules.hpp"
//
#include "serial_bridge_utils.hpp"
using namespace serial_bridge_utils;
//
// Shared code
//
// Test suites
 #include "../src/beldex_address_utils.hpp"
BOOST_AUTO_TEST_CASE(decodeAddress)
{
	string address = "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg";
	auto result = beldex::address_utils::decodedAddress(address, cryptonote::MAINNET);
	if (result.err_string) {
		std::cout << *result.err_string << endl;
		BOOST_REQUIRE(!result.err_string);
	}
	BOOST_REQUIRE(result.pub_viewKey_string != none);
	BOOST_REQUIRE(result.pub_spendKey_string != none);
	BOOST_REQUIRE(result.isSubaddress == false);
	BOOST_REQUIRE(result.paymentID_string == none);
	std::cout << "decodeAddress: " << address << std::endl;
}
//
//
#include "../src/beldex_paymentID_utils.hpp"
BOOST_AUTO_TEST_CASE(paymentID)
{
	string paymentID_string = beldex_paymentID_utils::new_short_plain_paymentID_string();
	std::cout << "paymentID: paymentID_string: " << paymentID_string << std::endl;
	BOOST_REQUIRE_MESSAGE(paymentID_string.size() == 16, "Expected payment ID to be of length 16");
	//
	crypto::hash parsed__payment_id;
	bool didParse = beldex_paymentID_utils::parse_payment_id(paymentID_string, parsed__payment_id);
	BOOST_REQUIRE_MESSAGE(didParse, "Couldn't parse payment ID");
	std::string parsed__payment_id_as_string = epee::string_tools::pod_to_hex(parsed__payment_id);
	BOOST_REQUIRE_MESSAGE(paymentID_string.compare(parsed__payment_id_as_string), "Expected parsed payment ID to equal original payment ID");
	std::cout << "paymentID: parsed__payment_id: " << parsed__payment_id << std::endl;
}
//
//
#include "../src/beldex_key_image_utils.hpp"
BOOST_AUTO_TEST_CASE(keyImage)
{
}
//
//
#include "../src/beldex_wallet_utils.hpp"
BOOST_AUTO_TEST_CASE(wallet)
{
}
//
//
#include "../src/beldex_transfer_utils.hpp"
#include "../src/beldex_fork_rules.hpp"


string pre_step2__unspent_outs_json = "{\"unspent_outs\": [{\"amount\": \"100000000\", \"public_key\": \"8b1e3ec8a3828f09845e3aec93b19c6788458df39b5045472739b896d7cb7c1b\", \"index\": 0, \"global_index\": 14205118, \"rct\": \"b746bda9aee02e971460efc3f9fe4243be305d724d2fb0ebbdc5f8abf31cdb909668123ad52a68f8\", \"tx_id\": 8225042, \"tx_hash\": \"ac8c1d9d89a289c7b2210c7cf94c5b03435b21e238557c2993246c1743c7cd5b\", \"tx_pub_key\": \"edc238c96cb30a739f56126ae962ac81be43e9aaa8a86313dec3d8ecfb36b7ef\", \"tx_prefix_hash\": \"293d3c03fdffa4e93600e51025287b37f1dc063a0cf22960d28f4ecf542aa516\", \"spend_key_images\": [\"d2d3db0a97ff7cde6774d2e8290559bf3e186e06783cb1ba39890bd31b0305ea\", \"44a97c766f23f1a471138fd1d5561b359f59c767498f829000cc8a17d6488abb\", \"73503ecb8c88eb6803df4f207901f9f57e847971d445bc232df13bb120c462d5\", \"5b6f0c36b6553ee3274037a37aaa7abdf4ad72900ce5ff588fe725652ab98665\", \"1d5447f30b261c8943d92289c80bb00973d363282fef06c086b2b660e88effae\", \"0b4b2e429aa59539de3ef6c55888307c6a6f6ea445c5f8e525a64a2f650ce5db\", \"0ff0bbaa87087449ae55d5df3a175050767c34b0186d53f8e64609b5af32d023\", \"070b01df752d5d9e4ffe54d587d3b63abcb3f7e73cec50047152c209f93372f7\", \"fddc4239b18fbe4232bec937ef5c1b399e7571ad720d6f527fccfe5c81d66c44\", \"0ecfa5b14b41473e368fc163f9b2e4f0118685d075edc01737bc75595cb20949\", \"8bbdf2254d173d77c1557b4d58e287eaca519d5d93a3b000062ebb423b1b59f5\", \"9ebc5f6db9c9d38ac3996ca98b7494dc3ab6c704134a3db845e54c54bc3510e9\", \"d8d7255ca9052b900bd738417b3ea49d0702c4865279ad888c4c4220ecd44f90\", \"5f57135e7f8c79b40c9d20eecd508409f594898c7369e205fed1e62a2be0fe6d\", \"1c8602ffbc7f1836425911d52c79a56f280c82c9ab9464a78bd9d1daa5a70ab3\"], \"height\": 2007212}]}";


string pre_step2__mix_outs_from_server_json = "{\"mix_outs\": [{\"amount\": \"0\", \"outputs\": [{\"global_index\": \"50942306\", \"public_key\": \"3657c7e0f604eb495943ae95991e5889135fa7e133e3ea1d1048f87c449dc87e\", \"rct\": \"0b928d8394d87ef7f10c78755b695912304698c4f468b42e8567acc5bc16097a\"}, {\"global_index\": \"60577669\", \"public_key\": \"f1726b7d52b86672a04db192ab64305e8153b60dd212d06343cd88e808dc0142\", \"rct\": \"ff3811d5cd57f6f5b05c01ec04a855414b43cb1ff7905467b9ad92e22411cc5f\"}, {\"global_index\": \"61273433\", \"public_key\": \"75a0758e3797b74428afa6f13717e9e5951eb5849770ebf4730ede81f8ba0f6c\", \"rct\": \"f891b6ebd377977e9f944d11c5465b741ab910241d3ad0d704305b3b82f4d0bf\"}, {\"global_index\": \"61383463\", \"public_key\": \"a42ec2b7f7c2811de7ae2c4072bdef66f0f1b8f3712d7ffdea63ad2c1925a198\", \"rct\": \"02105bd40764bd143835faee01106f8993d1aedc31832836477b41fa7084604e\"}, {\"global_index\": \"61448414\", \"public_key\": \"776c59a8cb5d9b7c29ef1fd03a65fc6ddd246f583977eab3a1c92b02c70e03a1\", \"rct\": \"825ba73ea802df9097ff1100163cabff4e1f1f97cf64f11c0dc45e4bc6c325e9\"}, {\"global_index\": \"61555488\", \"public_key\": \"214f05228207490c1d3398662f08b22e69bf980326c3e894b0dd7dfae42d5fa0\", \"rct\": \"e4f7c3866d996251cae66a375a3345e5b84ddac3b72cc5b048184d4928a92512\"}, {\"global_index\": \"61559370\", \"public_key\": \"3c8aeaeb788aa2fb3da3e8ccce650a321d7e95a7617a8102dba57383efcc01f2\", \"rct\": \"4ae24d80600ebde2af649f7de53238d392c3743406b5989de5ccc5e023cb9db2\"}, {\"global_index\": \"61562308\", \"public_key\": \"2059891bd03d6b2ed23c4b4b420e9441d82bf6184843ad1c5f95d796c3c882d5\", \"rct\": \"9509bccc2a25b319916a986344637758f4b979581433c260f5cc7c7464016807\"}, {\"global_index\": \"61564843\", \"public_key\": \"ab57323ed80da85fb83a225eb78272d299320ea4f66e6b7358ba40dba3be6fe3\", \"rct\": \"fed34bb387a22ef76def14466005ef07e58dcbd5b1f96fd4ac6e3ff1237f125e\"}, {\"global_index\": \"61567687\", \"public_key\": \"e7cc47dce8b6f94ae54ee58f558c83184001ce57fabc06ee4dda3e3fd2e1689c\", \"rct\": \"24f6bed05d641fcfc618d0dc6ac5dca0890517f93505e56bb615efdf72747513\"}, {\"global_index\": \"61576757\", \"public_key\": \"70b10448e15902f564eac79d853fe9aa79b0276446421197408c81dfc1037606\", \"rct\": \"73ab32c044dd6d81174183386f90b90b26f15480e62600f94788244fc5cd6da9\"}, {\"global_index\": \"61577007\", \"public_key\": \"d3a5a97935c101c8927ef1eabfae3e395f480f09fac0ea4f7fb51a7374c87aed\", \"rct\": \"476f08f2ab2ae6bd9d119946b5549ad5c940492dc5882d6ec7d7d2a40b757a31\"}, {\"global_index\": \"61578491\", \"public_key\": \"16b4a70669a8e9dfd4acf88c252f502845a65de3dedab399f57df9003f5b8173\", \"rct\": \"39de26b491fe55059cb9b7768b6aba01d8ec84cf9f01faa4415c003c79c3d1a6\"}, {\"global_index\": \"61580148\", \"public_key\": \"cf9cc1aef85da96e708809107dec6866e9575f7ed0aaa417154a27496cf06f1b\", \"rct\": \"8df361867ab912ece146f9606af51960bf01bc748ded7d57f2df641067a50d1a\"}, {\"global_index\": \"61583397\", \"public_key\": \"48826a239cc42a6f161b307242f742c4eceb753429ed52ef46cce09805aa615a\", \"rct\": \"ff7cf5cd5ba948f1e76a8f851b1e30b5f8681cf08824a9aea0d4450b5021a561\"}, {\"global_index\": \"61586681\", \"public_key\": \"561a56dfa3ac4fb36a4f375c67f9c9bdda52bcb02bd3b385c45192ed26740e66\", \"rct\": \"49053058aefc478055914dc7221277c84762409282c858ba2363f690010d5aaa\"}]}]}";
//
BOOST_AUTO_TEST_CASE(transfers__fee)
{
	uint8_t fork_version = 16;
	auto use_fork_rules_fn = beldex_fork_rules::make_use_fork_rules_fn(fork_version);
	uint64_t fee_per_b = 215;
	uint64_t fee_per_o = 100000;
	uint32_t priority = 2;
	uint64_t est_fee = beldex_fee_utils::estimated_tx_network_fee(fee_per_b,fee_per_o, priority, use_fork_rules_fn);
	std::cout << "transfers__fee: est_fee with fee_per_b " << fee_per_b << ": " << fee_per_o << ": " << est_fee << std::endl;
	BOOST_REQUIRE(est_fee > 0);
}
BOOST_AUTO_TEST_CASE(pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts__use_all_server_mix_outs)
{
	// *** START SETUP ***
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << pre_step2__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	//
	vector<beldex_transfer_utils::SpendableOutput> unspent_outs;
	for(boost::property_tree::ptree::value_type &output_desc : pt.get_child("unspent_outs"))
	{
		assert(output_desc.first.empty()); // array elements have no names
		beldex_transfer_utils::SpendableOutput out{};
		out.amount = stoull(output_desc.second.get<string>("amount"));
		out.public_key = output_desc.second.get<string>("public_key");
		out.rct = output_desc.second.get_optional<string>("rct");
		if (out.rct != none && (*out.rct).empty() == true) {
			out.rct = none;
		}
		out.global_index = stoull(output_desc.second.get<string>("global_index"));
		out.index = stoull(output_desc.second.get<string>("index"));
		out.tx_pub_key = output_desc.second.get<string>("tx_pub_key");
		//
		unspent_outs.push_back(std::move(out));
	}
	//
	vector<beldex_transfer_utils::RandomAmountOutputs> mix_outs_from_server;
	{
		boost::property_tree::ptree pt;
		stringstream ss;
		ss << pre_step2__mix_outs_from_server_json;
		boost::property_tree::json_parser::read_json(ss, pt);

		for(boost::property_tree::ptree::value_type &mix_out_desc : pt.get_child("mix_outs"))
		{
			assert(mix_out_desc.first.empty()); // array elements have no names
			auto amountAndOuts = beldex_transfer_utils::RandomAmountOutputs{};
			amountAndOuts.amount = stoull(mix_out_desc.second.get<string>("amount"));
			for(boost::property_tree::ptree::value_type &mix_out_output_desc : mix_out_desc.second.get_child("outputs"))
			{
				assert(mix_out_output_desc.first.empty()); // array elements have no names
				auto amountOutput = beldex_transfer_utils::RandomAmountOutput{};
				amountOutput.global_index = stoull(mix_out_output_desc.second.get<string>("global_index"));
				amountOutput.public_key = mix_out_output_desc.second.get<string>("public_key");
				amountOutput.rct = mix_out_output_desc.second.get_optional<string>("rct");
				amountAndOuts.outputs.push_back(std::move(amountOutput));
			}
			mix_outs_from_server.push_back(std::move(amountAndOuts));
		}
	}
	assert(unspent_outs.size() == mix_outs_from_server.size());
	// *** END SETUP ***
	//
	beldex_transfer_utils::Tie_Outs_to_Mix_Outs_RetVals tie_outs_to_mix_outs_retVals;
	beldex_transfer_utils::pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts(
		tie_outs_to_mix_outs_retVals,
		unspent_outs,
		mix_outs_from_server,
		boost::none/*prior_attempt_unspent_outs_to_mix_outs*/
	);
	//
	BOOST_REQUIRE_MESSAGE(tie_outs_to_mix_outs_retVals.errCode == beldex_transfer_utils::noError, "expected no error");
	BOOST_REQUIRE_MESSAGE(tie_outs_to_mix_outs_retVals.mix_outs.size() == mix_outs_from_server.size(), "expected resulting mix outs to use for step 2 to be same as server response");
	//
	for (size_t i = 0; i < unspent_outs.size(); ++i)
	{
		const vector<beldex_transfer_utils::RandomAmountOutput> &mix_outs = tie_outs_to_mix_outs_retVals.mix_outs[i].outputs;
		const beldex_transfer_utils::SpendableOutput &unspent_out = unspent_outs[i];
		const vector<beldex_transfer_utils::RandomAmountOutput> &tied_mix_outs = tie_outs_to_mix_outs_retVals.prior_attempt_unspent_outs_to_mix_outs_new[unspent_out.public_key];
		//
		BOOST_REQUIRE_MESSAGE(mix_outs.size() == tied_mix_outs.size(), "mix outs from server size does not match tied mix outs size");
		for (size_t j = 0; j < mix_outs.size(); ++j)
		{
			BOOST_REQUIRE_MESSAGE(mix_outs[j].global_index == tied_mix_outs[j].global_index, "new outs to mix outs did not tie as expected: global index");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].public_key == tied_mix_outs[j].public_key, "new outs to mix outs did not tie as expected: public key");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].rct == tied_mix_outs[j].rct, "new outs to mix outs did not tie as expected: rct");
			//
			BOOST_REQUIRE_MESSAGE(mix_outs[j].global_index == mix_outs_from_server[i].outputs[j].global_index, "mix outs to mix outs from server did not tie as expected: global index");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].public_key == mix_outs_from_server[i].outputs[j].public_key, "mix outs to mix outs from server did not tie as expected: public key");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].rct == mix_outs_from_server[i].outputs[j].rct, "mix outs to mix outs from server did not tie as expected: rct");
		}
	}
}
//
BOOST_AUTO_TEST_CASE(pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts__use_prior_attempt_mix_outs)
{
	// *** START SETUP ***
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << pre_step2__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	//
	vector<beldex_transfer_utils::SpendableOutput> unspent_outs;
	for(boost::property_tree::ptree::value_type &output_desc : pt.get_child("unspent_outs"))
	{
		assert(output_desc.first.empty()); // array elements have no names
		beldex_transfer_utils::SpendableOutput out{};
		out.amount = stoull(output_desc.second.get<string>("amount"));
		out.public_key = output_desc.second.get<string>("public_key");
		out.rct = output_desc.second.get_optional<string>("rct");
		if (out.rct != none && (*out.rct).empty() == true) {
			out.rct = none;
		}
		out.global_index = stoull(output_desc.second.get<string>("global_index"));
		out.index = stoull(output_desc.second.get<string>("index"));
		out.tx_pub_key = output_desc.second.get<string>("tx_pub_key");
		//
		unspent_outs.push_back(std::move(out));
	}
	//
	std::vector<beldex_transfer_utils::RandomAmountOutputs> mix_outs_from_server;
	beldex_transfer_utils::SpendableOutputToRandomAmountOutputs prior_attempt_unspent_outs_to_mix_outs;
	size_t index_of_unspent_out_used_in_prior_attempt = 0;
	{
		boost::property_tree::ptree pt;
		stringstream ss;
		ss << pre_step2__mix_outs_from_server_json;
		boost::property_tree::json_parser::read_json(ss, pt);
		//
		size_t i = 0;
		for(boost::property_tree::ptree::value_type &mix_out_desc : pt.get_child("mix_outs"))
		{
			assert(mix_out_desc.first.empty()); // array elements have no names
			auto amountAndOuts = beldex_transfer_utils::RandomAmountOutputs{};
			amountAndOuts.amount = stoull(mix_out_desc.second.get<string>("amount"));
			for(boost::property_tree::ptree::value_type &mix_out_output_desc : mix_out_desc.second.get_child("outputs"))
			{
				assert(mix_out_output_desc.first.empty()); // array elements have no names
				auto amountOutput = beldex_transfer_utils::RandomAmountOutput{};
				amountOutput.global_index = stoull(mix_out_output_desc.second.get<string>("global_index"));
				amountOutput.public_key = mix_out_output_desc.second.get<string>("public_key");
				amountOutput.rct = mix_out_output_desc.second.get_optional<string>("rct");
				amountAndOuts.outputs.push_back(std::move(amountOutput));
			}
			if (i == index_of_unspent_out_used_in_prior_attempt)
			{
				// will tie the first unspent output to the first set of mix outs returned from the server
				prior_attempt_unspent_outs_to_mix_outs[unspent_outs[i].public_key] = std::move(amountAndOuts.outputs);
			}
			else
			{
				mix_outs_from_server.push_back(std::move(amountAndOuts));
			}
			++i;
		}
	}
	assert(unspent_outs.size() == (1 + mix_outs_from_server.size()));
	// *** END SETUP ***
	//
	beldex_transfer_utils::Tie_Outs_to_Mix_Outs_RetVals tie_outs_to_mix_outs_retVals;
	beldex_transfer_utils::pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts(
		tie_outs_to_mix_outs_retVals,
		unspent_outs,
		mix_outs_from_server,
		prior_attempt_unspent_outs_to_mix_outs
	);
	//
	BOOST_REQUIRE_MESSAGE(tie_outs_to_mix_outs_retVals.errCode == beldex_transfer_utils::noError, "expected no error");
	BOOST_REQUIRE_MESSAGE(tie_outs_to_mix_outs_retVals.mix_outs.size() == unspent_outs.size(), "expected resulting mix outs to use for step 2 to be same as unspent_outs");
	//
	for (size_t i = 0; i < unspent_outs.size(); ++i)
	{
		const vector<beldex_transfer_utils::RandomAmountOutput> &mix_outs = tie_outs_to_mix_outs_retVals.mix_outs[i].outputs;
		const beldex_transfer_utils::SpendableOutput &unspent_out = unspent_outs[i];
		const vector<beldex_transfer_utils::RandomAmountOutput> &tied_mix_outs = tie_outs_to_mix_outs_retVals.prior_attempt_unspent_outs_to_mix_outs_new[unspent_out.public_key];
		//
		vector<beldex_transfer_utils::RandomAmountOutput> prior_tied_mix_outs;
		if (i == index_of_unspent_out_used_in_prior_attempt)
			prior_tied_mix_outs = prior_attempt_unspent_outs_to_mix_outs[unspent_out.public_key];
		//
		BOOST_REQUIRE_MESSAGE(mix_outs.size() == tied_mix_outs.size(), "mix outs from server size does not match tied mix outs size");
		for (size_t j = 0; j < mix_outs.size(); ++j)
		{
			BOOST_REQUIRE_MESSAGE(mix_outs[j].global_index == tied_mix_outs[j].global_index, "new outs to mix outs did not tie as expected: global index");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].public_key == tied_mix_outs[j].public_key, "new outs to mix outs did not tie as expected: public key");
			BOOST_REQUIRE_MESSAGE(mix_outs[j].rct == tied_mix_outs[j].rct, "new outs to mix outs did not tie as expected: rct");
			//
			if (i == index_of_unspent_out_used_in_prior_attempt)
			{
				BOOST_REQUIRE_MESSAGE(prior_tied_mix_outs[j].global_index == tied_mix_outs[j].global_index, "prior tied mix outs to tied mix outs from server did not tie as expected: global index");
				BOOST_REQUIRE_MESSAGE(prior_tied_mix_outs[j].public_key == tied_mix_outs[j].public_key, "prior tied mix outs to tied mix outs from server did not tie as expected: public key");
				BOOST_REQUIRE_MESSAGE(prior_tied_mix_outs[j].rct == tied_mix_outs[j].rct, "prior tied mix outs to tied mix outs from server did not tie as expected: rct");
			}
			else
			{
				beldex_transfer_utils::RandomAmountOutput server_mix_out = mix_outs_from_server[i - 1].outputs[j];
				BOOST_REQUIRE_MESSAGE(mix_outs[j].global_index == server_mix_out.global_index, "mix outs to mix outs from server did not tie as expected: global index");
				BOOST_REQUIRE_MESSAGE(mix_outs[j].public_key == server_mix_out.public_key, "mix outs to mix outs from server did not tie as expected: public key");
				BOOST_REQUIRE_MESSAGE(mix_outs[j].rct == server_mix_out.rct, "mix outs to mix outs from server did not tie as expected: rct");
			}
		}
	}
}
//
//
// Serialization bridge
//
#include "../src/serial_bridge_index.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
//
string args_string_from_root(const boost::property_tree::ptree &root)
{
	stringstream args_ss;
	boost::property_tree::write_json(args_ss, root, false/*pretty*/);
	//
	return args_ss.str();
}
//
//string DG_presweep__unspent_outs_json = "{\"unspent_outs\":[{\"amount\":\"210000000\",\"public_key\":\"89eb08cf704d4473a17646331d2c425307ef03477e5f18ee6a31a3601ba9cdd0\",\"index\":0,\"global_index\":7510705,\"rct\":\"befe623ad1dcae239e4d9d31e3080db5c339ea8c5c2894444966967a051f27839f1f713d6f6bdc13fec3c20f78bbae6cf08ce185273fa6c913db6ae1f44e270ea9dcfa48ecbae364125e0c4b0cb7a11fe6c250ec9aca1a668a0708e821d6550b\",\"tx_id\":5292354,\"tx_hash\":\"22fa4aaee9399901ece7d9521067aa7791a727ade2dfe9d5e17481800ccbc625\",\"tx_pub_key\":\"4f151192723d3d45372b43e4bf93df8ad7ba5283513c09226fd0603c60683e00\",\"tx_prefix_hash\":\"689580f0804eff0fd9bd76587ed9656e4cda8e70a33f065b5461206bcf9051b7\",\"height\":1681636},{\"amount\":\"230000000\",\"public_key\":\"f659694299d97fc93db504122d40dea1681a896567933635dc6337abc4339c10\",\"index\":1,\"global_index\":7551823,\"rct\":\"dd06d546553044cda0f083fd189cd8ad93ebeca557169eefe1e34dc48c6fac27110a3ff8dc24a61b595a03a034009a6d1f0ced61f19fb6e0d7c2b1a67bb39d06c7d5713e0a394551ec978b64927802f9307ac29c8ddec3857f551b945ef6a407\",\"tx_id\":5309604,\"tx_hash\":\"05704e7402d1373d14dccd383e4071bfae0c2af6eb075e67075b43fd7d26b4c4\",\"tx_pub_key\":\"3511d9117fdeac0423314827188aa187f1eb742a44ab0c01390053b68b00909c\",\"tx_prefix_hash\":\"1b89ac0c818454806686073cd2d6bd501923d6eec2c0e54e300e3ae68a2c5344\",\"height\":1684479},{\"amount\":\"50000000\",\"public_key\":\"6c0828f041fd3383b4823bd619fa9d130b83da8b10aa81bec1f1529890548542\",\"index\":0,\"global_index\":7552032,\"rct\":\"eb3291bd81992ec300e94e8f1bbf0bdfd7bb8b8ac5e1969f985f5642961e30f1bfaf72e1a284ac62da47184165091e2b8673143f8b5d533b9d2143c9e64e5f091a14169fa79f151579eac8e41102244aa148b6142121f5ad1b85d6404c04fd08\",\"tx_id\":5309676,\"tx_hash\":\"22c79cc2e5cefe5b1ed608021efc281f0eab6dbe4cc11051d59cb30b367a5120\",\"tx_pub_key\":\"471fe593e98e65529eeb2b60ad23ad0f7f879a51ef0a41ed34bb371bf346663f\",\"tx_prefix_hash\":\"6551844de3ba9ca5c0a58a8dfcb3fa6b74439c0f1054563ba7cd9a5eee26425d\",\"height\":1684494},{\"amount\":\"100000000\",\"public_key\":\"2721b9cf6cb9e4227cd4c58ea73be9c6e6ebf949d07e90f3cbfc624a18c91933\",\"index\":0,\"global_index\":7571542,\"rct\":\"14972c0692f37de21d4fe2e989262aaef574699258812b39908c6f9f28bfe80f07cae2373c7419eb41bde8425107cd3d87dd0211b1a59e92bad0b09789109d06620a1e4f80dbfa4ada1d432e55b3c23e965e858bc04effb64c473de0da3e4f0a\",\"tx_id\":5318071,\"tx_hash\":\"33fb202b7e1b2382838f17e5078311944870197536df0a560d73605023befcf7\",\"tx_pub_key\":\"3cb2a8fc531565dcc20477ec624fc1ffd60af9f491ab4ec5d54d4e4d6441d0c0\",\"tx_prefix_hash\":\"ce7bec7db0171da5e345103b7d38cdc19fc1db0655e4de8ecbf9b52d11b0ff51\",\"height\":1685790},{\"amount\":\"1630320000\",\"public_key\":\"437e101b61a526098adc98e46c8a674d2b3af3b79cf6ce8947e4effa2b545069\",\"index\":0,\"global_index\":7571614,\"rct\":\"026064f4989c3b19d99d4e3902a6800cdda39127449c639d0d9fcc31d9e4b297211cf6275f64d613cb7b553be07e1d738f72b138c4eaccb91970a10c513f2a005471ce338c4f3ea6bc07a37d10c32236af28c0e85d39ebdf8aa37ce2b9e5060f\",\"tx_id\":5318107,\"tx_hash\":\"19a98217e48c4db9c527dde5c7498317e2a6f258e31c87c3fe8d872d695b44f4\",\"tx_pub_key\":\"95c66b323352e10e7eee3220cc328f89b1b9dd5bfd2da4f61ba5dfcef923722c\",\"tx_prefix_hash\":\"0e053ddb7e60a64a8b501525963a61d8c182f82a66933486e77233055dbce3ac\",\"height\":1685794},{\"amount\":\"100000000\",\"public_key\":\"6a5982bf097116b68fe817abbd31b95821a0d851ac8e4ca34517b1cbe4449501\",\"index\":1,\"global_index\":7571710,\"rct\":\"6d8cd50a778f658b5e2ec7e7e1b8e19e80bb2ece759ed5e40398c33e5983722e45078078a6195d92c3f83d0f443d178a31156702c42f5c4b3e897e9931055f07173349088339daaa080c1f747a9025db0baa60b12beded6c7bc8ce893bda1700\",\"tx_id\":5318152,\"tx_hash\":\"7010c701459d2b897abbfed8f1dbc60b84c4fcd111afd7fcaf60eb1167c0a7a6\",\"tx_pub_key\":\"9321878b374c7f40021635bb03ed966217e5b8e7eb3e125839c55ae48d04ef81\",\"tx_prefix_hash\":\"edb575b5fd86b3e45214742454a4cfcc3d55f1ad457cc598c290dd69d9ebfa73\",\"height\":1685804}]}";

string DG_presweep__unspent_outs_json = "{\"unspent_outs\": [{\"amount\": \"100000000\", \"public_key\": \"8b1e3ec8a3828f09845e3aec93b19c6788458df39b5045472739b896d7cb7c1b\", \"index\": 0, \"global_index\": 14205118, \"rct\": \"b746bda9aee02e971460efc3f9fe4243be305d724d2fb0ebbdc5f8abf31cdb909668123ad52a68f8\", \"tx_id\": 8225042, \"tx_hash\": \"ac8c1d9d89a289c7b2210c7cf94c5b03435b21e238557c2993246c1743c7cd5b\", \"tx_pub_key\": \"edc238c96cb30a739f56126ae962ac81be43e9aaa8a86313dec3d8ecfb36b7ef\", \"tx_prefix_hash\": \"293d3c03fdffa4e93600e51025287b37f1dc063a0cf22960d28f4ecf542aa516\", \"spend_key_images\": [\"d2d3db0a97ff7cde6774d2e8290559bf3e186e06783cb1ba39890bd31b0305ea\", \"44a97c766f23f1a471138fd1d5561b359f59c767498f829000cc8a17d6488abb\", \"73503ecb8c88eb6803df4f207901f9f57e847971d445bc232df13bb120c462d5\", \"5b6f0c36b6553ee3274037a37aaa7abdf4ad72900ce5ff588fe725652ab98665\", \"1d5447f30b261c8943d92289c80bb00973d363282fef06c086b2b660e88effae\", \"0b4b2e429aa59539de3ef6c55888307c6a6f6ea445c5f8e525a64a2f650ce5db\", \"0ff0bbaa87087449ae55d5df3a175050767c34b0186d53f8e64609b5af32d023\", \"070b01df752d5d9e4ffe54d587d3b63abcb3f7e73cec50047152c209f93372f7\", \"fddc4239b18fbe4232bec937ef5c1b399e7571ad720d6f527fccfe5c81d66c44\", \"0ecfa5b14b41473e368fc163f9b2e4f0118685d075edc01737bc75595cb20949\", \"8bbdf2254d173d77c1557b4d58e287eaca519d5d93a3b000062ebb423b1b59f5\", \"9ebc5f6db9c9d38ac3996ca98b7494dc3ab6c704134a3db845e54c54bc3510e9\", \"d8d7255ca9052b900bd738417b3ea49d0702c4865279ad888c4c4220ecd44f90\", \"5f57135e7f8c79b40c9d20eecd508409f594898c7369e205fed1e62a2be0fe6d\", \"1c8602ffbc7f1836425911d52c79a56f280c82c9ab9464a78bd9d1daa5a70ab3\"], \"height\": 2007212}]}";

//
//string DG_presweep__rand_outs_json = "{\"mix_outs\":[{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6986524\",\"public_key\":\"3ce9f1231ecebf100a8d0e9c165a2b88a766249cb03eac2c6dbe7587a1f0e9ae\",\"rct\":\"c3b81a937c12c017b4c4eee0ab9acbd10d83f28c1586971b13791c7b475e469b\"},{\"global_index\":\"7282304\",\"public_key\":\"278450b855e4d66dbc1a9ae2801a2f101a10afd22c27466c3cfcc3b434a25047\",\"rct\":\"dd05d1d973be19b4e754c24c6d21e9252a9b99db52ff291930d4cd8c1cd344df\"},{\"global_index\":\"7386837\",\"public_key\":\"0d3cf94dd4e9059900f14bd8d5b71ce43e444efd2b8a1a63a1f9705851d195a1\",\"rct\":\"5c124e0c007e8a2f6371a6d35d50165178667fa9470270e8d7a95ffda34df30d\"},{\"global_index\":\"7459325\",\"public_key\":\"badabeeb71f08917b0cb76ae128e869dab7291d58c7a6b2fbd31d3eed0f003df\",\"rct\":\"a5ca005346fad19624c185dfefb2c4013f6b769f0f0de4b2c8f507ede1cb46a5\"},{\"global_index\":\"7507948\",\"public_key\":\"6f08278bc9d064cfdaa6d896ef70d28fbb3dca84e0a99ea21325f9aaef3bd783\",\"rct\":\"4a70f95a4cc19d9e43cc6b60f30f60571029240df21fb06188766bf92e8d8738\"},{\"global_index\":\"7529692\",\"public_key\":\"8b13f88507f5ca60c72c076ce6bc8ee142abc6e5115ab0c08e10a919c93f912a\",\"rct\":\"6055a2a847938471bd6f00a4d9789e6dc9d70962bb1dc2f51879d04211aaa0b7\"},{\"global_index\":\"7563051\",\"public_key\":\"d44a722cdca3c372081af6e32b758a2bbab9f2534f68a08b71d38c3540209c50\",\"rct\":\"b5ebd41d0c75877cdf109d6b5939072c22a84aee4c46a8299bec8eafc82789e9\"},{\"global_index\":\"7564143\",\"public_key\":\"c12f9e3c53dee0d1327dbca66129b27f8c6174a777976615ee442278960ba369\",\"rct\":\"a8423b9491162813589d3af5e18677f2f38050c10cb5074c097f101ccef089c5\"},{\"global_index\":\"7567982\",\"public_key\":\"9e4347089b0e1cb065cb443899d77b4bd4d61598e80a8946336440920c8a6731\",\"rct\":\"00fc0e9c631a4a2538785b647e6146ba39743d9dc987059f850d1c5a4f97bd2b\"},{\"global_index\":\"7570259\",\"public_key\":\"1be949046425c646a86ac37961a6301ea3d25711426d80a48b11e9282acd222b\",\"rct\":\"7db9d60ac0286189a1833f39db7f3e5372763c557fe2240b4537bf580a902798\"},{\"global_index\":\"7570451\",\"public_key\":\"82a27a521340220805de27aae18a4663b81067145c0b0c3e7ec42341067bf270\",\"rct\":\"a3f46fdc3e4a252604e3f3d082ab1d2cbc3ce34bf62b641b76849c5382199a32\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"7442603\",\"public_key\":\"ba89de37e26056629c89b14b3b05a73400c62149fa0de2794d3876f17faeb28f\",\"rct\":\"aa2edfca6622db354add0813ff2b471f6dc20f0d9e56d1f9b6c04b1369ceb1a9\"},{\"global_index\":\"7445670\",\"public_key\":\"a0c3a8bd0d6fa37e7bd514a10ebe6970609919e2f781dc489b771f305f1da4cc\",\"rct\":\"eb78b914307a54cd95481ba8844df3dd2d12cd14cee07de441c2c607b9cfcb24\"},{\"global_index\":\"7474646\",\"public_key\":\"3d325a1222b77d82192e1c051b241e0f79e1cc731c5f03749df33cf1a7165be8\",\"rct\":\"821bfcb255fc815aeab23d890ba252dc590c743c5733bcd278dbd1763e921e4d\"},{\"global_index\":\"7545722\",\"public_key\":\"ec62838ef1ab75055940fd8f31126698af9ff2128a53def09bdaa0d315174d80\",\"rct\":\"547de3a10658167afee6aaf8f3481921d2b1ee3014d40fa4cacc86940b244985\"},{\"global_index\":\"7556262\",\"public_key\":\"4dab027c001473b775f70503b9d68c156d2a8bfa0d7534aaff12a2ab1d8d5f89\",\"rct\":\"5aa838a2f5450408932b53181899861600d3cac864dee8197ac7e9543fbab148\"},{\"global_index\":\"7557709\",\"public_key\":\"bd1813a780e4df3c8ba25b825c3d7be12ce8c5d05f6731384e0d2d8cb8bf3134\",\"rct\":\"49ce757933cdca4a51f77ae41b951a2175d0a0a0378c10c3a02432e5aeb9f79f\"},{\"global_index\":\"7560040\",\"public_key\":\"ea53143df34ccba3c29743964ddc14094f224fa92d45c8fa8e86d7ff1394e51a\",\"rct\":\"455a6083ab6c3d4f026d2b4e1545467666f7affa0cdec365a295c097eefeac46\"},{\"global_index\":\"7563671\",\"public_key\":\"9af80a727bdb148851e79a9a11f55e97435daf65b3d57b54f4d64833cd483f2b\",\"rct\":\"622855010cd03a04d66d71a20d6113cb0507276b4c6ef050297a12e0a6767004\"},{\"global_index\":\"7564234\",\"public_key\":\"404aedc1c299e9a1538bdf7619f42cbf92cb3bb556e0356dce275945e318633d\",\"rct\":\"a1978e496622c2fac054939227a4edb31c4a50215cf8db74b0f1a7ce3477e3cf\"},{\"global_index\":\"7565705\",\"public_key\":\"070c5adc791d0a33390fecb02376e8953e46661a0173a64c003b5ae5709eea3c\",\"rct\":\"09f6c3c9139eefa0ed9ff9613e57bf3fc1b7d2bc42bad4caeb9118cc768cc52f\"},{\"global_index\":\"7566892\",\"public_key\":\"76c03aad2fae21aa7d36bbda699c462b222a76359d92813c06e4ccf4508e77e2\",\"rct\":\"9905946004a01e2884aedfa41b2482ca309226166519c558b5c794eeae109f98\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6898616\",\"public_key\":\"7078ee4031355ca5a60edf9e0240d8c5d42ed180d736628b9386c4cc1dc1cee9\",\"rct\":\"d9a90792ab31fe09094daf43bf1c5f897fac77cd45d72accb5735bb4fe2d98f3\"},{\"global_index\":\"7125047\",\"public_key\":\"556a3792556978326baf4e1cd792c9f8b36f2090afddfd929bf0f87d5b119828\",\"rct\":\"8a9653cbe1b879e562849ff5187af02f49e67b351fda5d39319cffd2a33f56f2\"},{\"global_index\":\"7341447\",\"public_key\":\"f3312f6841d03044e768305ec6166c82917676335a4a751734f2708dfa1dcd97\",\"rct\":\"d20cee9952491177cd1527958c3d57cdc2145f76562f4ab87243349c52318427\"},{\"global_index\":\"7388641\",\"public_key\":\"c3477733871b3a696a81470471ec3996acc27a7ff4c03a899fbec02533c27511\",\"rct\":\"5236a3e790c98624d398e6fbe45b6035da0e4202ac01731722608821a3400d48\"},{\"global_index\":\"7417267\",\"public_key\":\"68f0fa9eefd3fcb6be31ddc49091057b4cf262f4e7500ac85eef93ac32804f5e\",\"rct\":\"e7045d968d7dcbbbdb4f1c3e75703b5f8a151e2381bc44f5f8dc754ea41d0e21\"},{\"global_index\":\"7519867\",\"public_key\":\"d7c4b74dbfb8d00d1e7476124a85e8f756c4a0fa4448aa491acbae3a79500d66\",\"rct\":\"2bbdf12767b7be6d4f15c629cc8c6ce24b63880c15ad7c55c3232ed1d63712c8\"},{\"global_index\":\"7559496\",\"public_key\":\"f06a43153a2c77b55e9af88d21b8c582550d0c03e0ee84492f01aadd1b4c5a7a\",\"rct\":\"f34595267477768ca348689279c4cf2cf4b3f51293015255379aac5b8460afb0\"},{\"global_index\":\"7570229\",\"public_key\":\"a08bf753c3f12ae97702bb30e192d63e62f07558cd7632def98921a2275414a7\",\"rct\":\"a9df67974d97999626c02c72dc1adc90e9bfaaf16742ecccb7e230110a4a3aea\"},{\"global_index\":\"7570862\",\"public_key\":\"174f1d11a4f5c6a08b04dce4c03850faecaae619b3f93d7004754f0a00a49839\",\"rct\":\"9820922f314045452a6022e8cd1c7f5557fd8784194808af1ed0e5f4ba0e7588\"},{\"global_index\":\"7571034\",\"public_key\":\"8859cfe384706c05806818dd77684a7a07c6bff3516c68906871ffeb83a20d60\",\"rct\":\"ad21afb2b1615bead1204096cb412799f0bf89f46411e917f3ba762897d53ff3\"},{\"global_index\":\"7571342\",\"public_key\":\"9292b038cdffeddc25e71356eb5850528e7e8e2b3c877535ffc8eaab4282c225\",\"rct\":\"009da46a328a043b87b774f518018aead88b4c46fd0b412880cdf07b25f52bd3\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6378847\",\"public_key\":\"acc97fed526da1168e8a5aa0bb04c6c2e79f84f2f2cc22c00397d016306226d5\",\"rct\":\"5bff394cf377ca3cfba831c9a3cc70b2cb3e95dfb26773136a61ec720c2d4fda\"},{\"global_index\":\"7450246\",\"public_key\":\"bd8b3c4f38adecb30ea18dbab7512cddb89246ea60319f2eee80b2554455bbd4\",\"rct\":\"add46baca4f3b914b0d2e3ce9f4c568c99331e47ec9f4fcbc8a8ca4ef9f49605\"},{\"global_index\":\"7473242\",\"public_key\":\"b88d96d641378412168bcf80b1c643a79d2e0f503b6cac39ed693042754f6ee3\",\"rct\":\"4ecb6a92321d83a953fceec22516a1ca5d50900dd6cccc4e17abdc70b3328514\"},{\"global_index\":\"7525156\",\"public_key\":\"d3bf363e284257dd2cb24216d1d58ecf5dafedff893d8ada5d28f4c2ad9ef494\",\"rct\":\"d945fd6c04810b99323b3563749fbcd4b1efeda08796394ad05cbcc30c54508a\"},{\"global_index\":\"7531713\",\"public_key\":\"46ea1435fcbae0db704087462eed3a47cff93f738ee51881fc779d248b65fefa\",\"rct\":\"604f96bccca4f79ae7ccce8a5317baa5cd65685dc26dde888cc9049c845bb3d9\"},{\"global_index\":\"7542701\",\"public_key\":\"2319ab37a81b9b012bed4b952ce4c7b85173ea7fa9ed104dcb767580f0af2d1b\",\"rct\":\"3057ece8d0c4a536c4ffa7ff5812b9ba0c951af2b9aa7c788d4d8668480e7f5e\"},{\"global_index\":\"7553340\",\"public_key\":\"e79aa59e773211c29d696aaf5173b4d58e21a6bd8da693d8bf83c6cdf83cfdbc\",\"rct\":\"7d3afea7adf3b3fd946a9b0f4a60616179a5f3cd25027e9a88e9753219ad6a4a\"},{\"global_index\":\"7556989\",\"public_key\":\"33230357a71d8ebeb619a3b613d1d6519090c6b0a208f7c7679f2aac7258ce03\",\"rct\":\"61e1ec7ed3d400d484564687bb18975e73693c47cf9db8bcb0bf3de53c82cfb3\"},{\"global_index\":\"7564935\",\"public_key\":\"8104c3baa28dd4b48554392d7f8bc999e4a0bf3b04a0c11237b17ed0814122ce\",\"rct\":\"5d54aad47d92ada5212ab8f2968799d7235ac27c4497f17143e5cb2b562d210e\"},{\"global_index\":\"7568940\",\"public_key\":\"e750b10591f8ee3f337a55b6490423d31e9b45899d228fed818811c15176667e\",\"rct\":\"37a8725d2d5af7c4dfbbde8cd54f1b1cbfcbe9f8733d2dbb9a1260c1fac437b7\"},{\"global_index\":\"7569092\",\"public_key\":\"74a6306059946b700bb2fde08a12921c799bfb18bbf775246c1dec26c3d5e14b\",\"rct\":\"a4d1566adf3d52a55a518c1533b9ab7ca6bf74e27121cc79c4f15b3b1dc60cdd\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"4720715\",\"public_key\":\"8b397b7ee91577dd3f30b86245ec351f8906ac0eadf947f17ee0c6e4b5233a39\",\"rct\":\"2f0ed876b848ecb80647d991082afed2d6f48af3b329757a6cdd84aa323713f4\"},{\"global_index\":\"6747843\",\"public_key\":\"dde0018c7f8c8436907cb62d2b1ed92c14eceafe72cdce3cfacf539b795c2d22\",\"rct\":\"c7867e3f79c322fd2b6d290f76798a8e5626e52df5823d82c5dcdabace44982a\"},{\"global_index\":\"6798372\",\"public_key\":\"955ea5eac6ae37465657c8d3893984fe363f04423889a399ab55261395e1cc05\",\"rct\":\"146f973c2e6644cb39129e2f0127391a1f560fc5235aa8b9afb790a02fa75bac\"},{\"global_index\":\"7141175\",\"public_key\":\"d4db04b8b1dd4b723265b5dcb13ecb0cd4eec8c29580bae631298456717f233a\",\"rct\":\"75908e57c797b43d8c15ec507d03b5785c0e16ef637b4be259638e1e8e7f05e4\"},{\"global_index\":\"7211806\",\"public_key\":\"a68526d2a7d29140473e2d6af52d6487f9c1093caa638d0b6abe21a31ceda161\",\"rct\":\"2beb25022d6b9907ba0678197e0eec0b2edf7bfc6881a66106d43928678ea716\"},{\"global_index\":\"7553092\",\"public_key\":\"d2bf03a9c05de99e250822467e26672b2da3c86feb922ebfcaa4df8c8e2d6e5b\",\"rct\":\"7e06be8140eeb284d687a6d371690877208af23099c2ecd4301bfdd160068c32\"},{\"global_index\":\"7560413\",\"public_key\":\"65ea9940f971560c0cfb0099807c01d63aea0e9cdad98077b4b5abe3e15ffff7\",\"rct\":\"c889ad6c6f2ea64ad43396043ae0421f40567c4778ae89577dd510e992c6d7b5\"},{\"global_index\":\"7562968\",\"public_key\":\"74f327f9a8f2ace334605247c37d52f195f21cb319293e10944855ed8395e18f\",\"rct\":\"c9320c745df7a9dce32ac0ead1d673e4b3faf6034e7efd19bc977f493c6bff4e\"},{\"global_index\":\"7566433\",\"public_key\":\"9620705dead2c2d3665c0787dffb0267362e14d5e509489c9e95f3cfdc3c8457\",\"rct\":\"9a183845a8690f07fa42bb4c442656936ef80e5cb8a859212bd54ec0128934dd\"},{\"global_index\":\"7568871\",\"public_key\":\"fe921b107a193fe4aab99d81df26003eabd62d8e2547eb3d1dd8ebe4c59da7bf\",\"rct\":\"a8b0c65e2c3b4db5e115420fa7eeb897e68e00753e0286491a37f8827f3dd568\"},{\"global_index\":\"7569156\",\"public_key\":\"d2ff286caa1f62bf30c261075d954f517530aed5fa3c74649df19a139dc179f9\",\"rct\":\"40ae688dcf89f2977b2b02c962ead32c205fd72353236aaeb73bec97df788f66\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"2633596\",\"public_key\":\"9201769d3105e2c601fc748dde2d265aa8482941df2dd63667ddcfb5c8d0175c\",\"rct\":\"d4254c3aaaeb3328396cf042e4b10cd61a712569349406038621c0b061f97f70\"},{\"global_index\":\"7263762\",\"public_key\":\"bcdc4d2dea674cb7b7c8c65fbb6060ce9ee5f3449e6c65cea258ab1193b9bc35\",\"rct\":\"4e48a02f7056d19234ed1b21ca50344688fc737cd3a21df3f6292283c34db055\"},{\"global_index\":\"7373692\",\"public_key\":\"462f51785b1d90e554d72ebae7db4c0d4fbef32341b260a19fdccfec33d33cfa\",\"rct\":\"7419c1330bcdec0a8b0989b9a1c5d0455862e040b597c58591df8bdf92f433e2\"},{\"global_index\":\"7450519\",\"public_key\":\"48843aeaa09ed9c76aa9083f561a90ec9eca05df4e10fc8a9ae9cef11ab8661c\",\"rct\":\"8d79dfc05adbb2d47d3542eeb33b05e8c7db80d73961d7d99f240713e9f8c63f\"},{\"global_index\":\"7490436\",\"public_key\":\"1f9ee1cad77da88655e6164f8e863674b465257235ea1a219d8cb79f583e1554\",\"rct\":\"8018a907a77fd45ac5bbeca3cf1f7def348fa919978035503d51292622981b33\"},{\"global_index\":\"7531503\",\"public_key\":\"ff195ccc3f09483ce926c499ecdd525b5706148de996f7c506cc3d25db6e3e20\",\"rct\":\"db6e2ba255a3e3be8e00c1cc4a3de24037e36c1861e1092bcf61831d306d873e\"},{\"global_index\":\"7539183\",\"public_key\":\"7ef9ff4f7eeb1fccd290e01ae4fc6bdd88aaeb1742cd4715781f029d0d60a3c8\",\"rct\":\"14b2e69d5f77d9a125a9ee6042b636b5b3305c830f6d1ecf71d5e7c37f1f1941\"},{\"global_index\":\"7563953\",\"public_key\":\"b6523d8a24ca46db67671aec10d521aa990fdc5e6beac2cafcc829f512be1058\",\"rct\":\"b92decdcb4b0a9ca3dd233b6c0293691921211bc08db073e611bf0ec4524d121\"},{\"global_index\":\"7566210\",\"public_key\":\"d994890e9026a5830c6363261355e08d84d008c1d798b92887714a0e1dcdfc27\",\"rct\":\"aa9c6b3f6bb6f196e01b0bcf1a0ce9b9bc0cee72b8e37fcc3f06b87dd66bf81f\"},{\"global_index\":\"7566970\",\"public_key\":\"3684782e3eef48a3ce46b8b9fa0848003744847e6c649f5f45a973fb7ecb86ea\",\"rct\":\"03817bc1c51d5d37e12ecc032ad09a1cf679a39ba969a50d2e0ffda124bb8a80\"},{\"global_index\":\"7570610\",\"public_key\":\"006e51f0e4a3fbbfa3a4c1886c6917ae823f12eebe322da60da6f030f54c1a1d\",\"rct\":\"1250a56450cf2a41d19c4148e8a3466ef6f169aa036ae022a4fc70505c8e7b5b\"}]}]}";

string DG_presweep__rand_outs_json = "{\"mix_outs\": [{\"amount\": \"0\", \"outputs\": [{\"global_index\": \"49952096\", \"public_key\": \"4afb1bd97564ec021fd7f1a6a8d50a6275a95bd546c2ccbf9cd7138ef7651004\", \"rct\": \"ce5763ef7de3902b45816c99b5c33cfce0a410b9714c0cb77ed72cd0e40f9a05\"}, {\"global_index\": \"59489005\", \"public_key\": \"db0ef8523a6b24ba3ecc068d2fd5d6490b2ff51d5389f867fc1a5c0fe6a0b774\", \"rct\": \"95978f16e9a2a380d681ddb6292d0d6d0a25979ed0812b58a6afc1777e928986\"}, {\"global_index\": \"60685504\", \"public_key\": \"ed8826ce1f63409e885d20e732abd408dd20cb80b74f96d9107f76c58eb56e68\", \"rct\": \"f0b534222d7387fd105f978cb5fda546279f46f6e065a1cf1120f088b2904036\"}, {\"global_index\": \"60693681\", \"public_key\": \"df457d224e8ed430577f724767fc39b61c61e9c20f88ba32a0d51458039b4800\", \"rct\": \"b59d1dc28c258f752ca1f4b83ea0735f196212d7f8bd63a4dc4e29618c649b55\"}, {\"global_index\": \"61235782\", \"public_key\": \"dda0a77edf12817b7fe0bc535a77dd9df65155f0c0b9c3b553c7c671251d8dff\", \"rct\": \"df43eff3157f80c1dee756a4a861299bc734191b1a0ed35245047a167ed4bfe7\"}, {\"global_index\": \"61481398\", \"public_key\": \"13dee47bcd7cddadb733d16ba22096ca84dc5a0a7e7ce274a41432c18e755a13\", \"rct\": \"3406ab4191f572be6ec5f2a58b53dda53d008e5bb584f1f2ccd7ea9829a8b1e7\"}, {\"global_index\": \"61505686\", \"public_key\": \"edb828f3c33c054aead7469ac5d87d8c288014048959263326b493dcc98ba4ff\", \"rct\": \"849be78735f28cfce2732bb9d3d0b13f2b5d812c5a0aff2dbbe2ff35c9c805c0\"}, {\"global_index\": \"61519922\", \"public_key\": \"dffcf0bf482ded577c9d7735ce99a7fd41d987f8a31c5645a092e5fc59716a8f\", \"rct\": \"55b7158363876dcb78ae4a4dc8bcace07cd8facda828ff1cbf4b5d30415f6e8b\"}, {\"global_index\": \"61544588\", \"public_key\": \"fab9a89d1e5e6f42e3d9d77302b38242b8826069aadee29c2a17fbe0f28b160f\", \"rct\": \"32f09ce8e70634751f6b3e3952718652eba24d6d4450f5b108ab29be91547b8a\"}, {\"global_index\": \"61566420\", \"public_key\": \"3baf20212b2a05a08cc30406acd1f93bbe8e9fa96f2642fba07de67aab8eb6a3\", \"rct\": \"74028195774059c3653eb18fa6e3b964185b3b10dd7bf755f4939fa30371ff1b\"}, {\"global_index\": \"61574768\", \"public_key\": \"1401cd5a1c1a05c240885cd69c508f0c6a4e4e64ffc826f618d59190ae2a7597\", \"rct\": \"2b3e4386e824e6c1ac8ae6b50d4672d94e1819cdd60b48ce8d161ac0a92fbcee\"}, {\"global_index\": \"61576994\", \"public_key\": \"0bd182a0de66faf2c6f0fd1bc59b027138fba2e8285dad9873f3a0c7f7297669\", \"rct\": \"c5b324b67878558485966e51c74747c66ec283b7784ce0b982dc8c418720694a\"}, {\"global_index\": \"61585529\", \"public_key\": \"735ec711fd19536892a22b4127cc9c0443bbc6c1fe81c655a0b8b3add8b691a4\", \"rct\": \"6e3fd82711b1701941c7bd6446e5a11285f718853ef2d6b5c3ace023048e7ad0\"}, {\"global_index\": \"61586305\", \"public_key\": \"0017b8485143fcb2d632f8a1c71ba687eb8c854622b05b55ba603c308bb4c069\", \"rct\": \"f62fad64eba277e57800194266cb5dc8f6a8057823fabee3660b979cd6374612\"}, {\"global_index\": \"61586375\", \"public_key\": \"fb85a784f2cf713e07e26341ef1a3ad5ae3237411edcafe333a26bdc047e202e\", \"rct\": \"d02312c78234a5729a9f10ecb6a0d1848677348698cfaa29e7947d0724362a1c\"}, {\"global_index\": \"61587619\", \"public_key\": \"19e5e4d3202dd35f4b4e4913c84c73df95b0a3362046d638681fe1b376b67ac7\", \"rct\": \"19bd7c89fc5a6ae18dc9ef1ce6392f49ebee2998ec00191313060bad14c63387\"}]}]}";

//
BOOST_AUTO_TEST_CASE(bridge__transfers__send__sweepDust)
{
	using namespace serial_bridge;
	using namespace beldex_transfer_utils;
	//
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << DG_presweep__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	boost::property_tree::ptree unspent_outs = pt.get_child("unspent_outs");
	boost::optional<boost::property_tree::ptree> prior_attempt_unspent_outs_to_mix_outs = none;
	//
	//
	// Send algorithm:
	// (Not implemented in C++ b/c the algorithm is split at the points (function interfaces) where requests must be done in e.g. JS-land, and implementing the retry integration in C++ would effectively be emscripten-only since it'd have to call out to C++. Plus this lets us retain the choice to retain synchrony
	bool tx_must_be_reconstructed = true; // for ease of writing this code, start this off true & structure whole thing as while loop
	boost::optional<string> fee_actually_needed_string = none;
	size_t construction_attempt_n = 0;
	while (tx_must_be_reconstructed) {
		construction_attempt_n += 1; // merely kept for assertion purposes
		//
		boost::optional<string> mixin_string;
		boost::optional<string> change_amount_string;
		boost::optional<string> using_fee_string;
		boost::optional<string> final_total_wo_fee_string;
		boost::property_tree::ptree using_outs;
		{
			boost::property_tree::ptree root;
			root.put("is_sweeping", "true");
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("sending_amount", "0");
			root.put("fee_per_b", "24658");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("priority", "1");
			root.add_child("unspent_outs", unspent_outs);
			if (fee_actually_needed_string != none) {
				BOOST_REQUIRE(construction_attempt_n > 1);
				BOOST_REQUIRE(prior_attempt_unspent_outs_to_mix_outs != none);
				//
				// for next round's integration - if it needs to re-enter... arg "prior_attempt_size_calcd_fee" and "prior_attempt_unspent_outs_to_mix_outs"
				root.put("prior_attempt_size_calcd_fee", *fee_actually_needed_string);
				for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
				{
					string out_pub_key = outs_to_mix_outs_desc.first;
					cout << "bridge__transfers__send__sweepDust: step1: prior output " << out_pub_key << endl;
					BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
				}
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			auto ret_string = serial_bridge::send_step1__prepare_params_for_get_decoys(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::ptree ret_tree;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				if ((CreateTransactionErrorCode)*err_code == beldex_transfer_utils::needMoreMoneyThanFound) {
					boost::optional<string> spendable_balance_string = ret_tree.get_optional<string>("spendable_balance");
					BOOST_REQUIRE(spendable_balance_string != none);
					BOOST_REQUIRE((*spendable_balance_string).size() > 0);
		//			uint64_t fee = stoull(*fee_string);
		//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send__sweepDust: step1: needMoreMoneyThanFound: spendable_balance " << *spendable_balance_string << endl;
					//
					boost::optional<string> required_balance_string = ret_tree.get_optional<string>("required_balance");
					BOOST_REQUIRE(required_balance_string != none);
					BOOST_REQUIRE((*required_balance_string).size() > 0);
		//			uint64_t fee = stoull(*fee_string);
		//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send__sweepDust: step1: needMoreMoneyThanFound: required_balance " << *required_balance_string << endl;
				}
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
				// ^--- not expecting anything like needMoreMoneyThanFound errors here
			}
			mixin_string = ret_tree.get_optional<string>("mixin");
			BOOST_REQUIRE(mixin_string != none);
			BOOST_REQUIRE((*mixin_string).size() > 0);
			uint64_t mixin = stoull(*mixin_string);
			BOOST_REQUIRE(mixin == 15);
			cout << "bridge__transfers__send__sweepDust: mixin " << *mixin_string << endl;
			//
			using_fee_string = ret_tree.get_optional<string>("using_fee"); // save this
			BOOST_REQUIRE(using_fee_string != none);
			BOOST_REQUIRE((*using_fee_string).size() > 0);
	//		uint64_t using_fee = stoull(*using_fee_string);
		//	BOOST_REQUIRE(using_fee == 10); // TODO:?
			cout << "bridge__transfers__send__sweepDust: step1: using_fee " << *using_fee_string << endl;
			//
			using_outs = ret_tree.get_child("using_outs"); // save this for step2
			for(boost::property_tree::ptree::value_type &output_desc : using_outs)
			{
				assert(output_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send__sweepDust: step1: using_out " << output_desc.second.get<string>("public_key") << endl;
			}
			//
			change_amount_string = ret_tree.get_optional<string>("change_amount");
			BOOST_REQUIRE(change_amount_string != none);
			BOOST_REQUIRE((*change_amount_string).size() > 0);
	//		uint64_t change_amount = stoull(*change_amount_string);
			//	BOOST_REQUIRE(change_amount == 10); // TODO:?
			cout << "bridge__transfers__send__sweepDust: step1: change_amount " << *change_amount_string << endl;
			//
			final_total_wo_fee_string = ret_tree.get_optional<string>("final_total_wo_fee");
			BOOST_REQUIRE(final_total_wo_fee_string != none);
			BOOST_REQUIRE((*final_total_wo_fee_string).size() > 0);
	//		uint64_t final_total_wo_fee = stoull(*final_total_wo_fee_string);
			//	BOOST_REQUIRE(final_total_wo_fee == 10); // TODO:?
			cout << "bridge__transfers__send__sweepDust: step1: final_total_wo_fee " << *final_total_wo_fee_string << endl;
			//
		}
		boost::property_tree::ptree mix_outs;
		{
			boost::property_tree::ptree root;
			root.add_child("using_outs", using_outs); // from step1
			// NOTE: in the real algorithm you should request _previously unseen
			// mixouts from prior attempts each time pre_step2 must be called_
			// this being input as JSON merely for convenience
			boost::property_tree::ptree mix_outs_from_server;
			if (construction_attempt_n == 1)
			{
				boost::property_tree::ptree pt;
				stringstream ss;
				ss << DG_presweep__rand_outs_json;
				boost::property_tree::json_parser::read_json(ss, pt);
				mix_outs_from_server = pt.get_child("mix_outs");
			}
			else
			{
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			root.add_child("mix_outs", mix_outs_from_server);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>(ret_json_key__any__err_code());
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			mix_outs = ret_tree.get_child(ret_json_key__send__mix_outs());
			BOOST_REQUIRE(mix_outs.size() == using_outs.size());
			for(boost::property_tree::ptree::value_type &mix_out_desc : mix_outs)
			{
				assert(mix_out_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send__sweepDust: pre_step2: amount " << mix_out_desc.second.get<string>("amount") << endl;
				BOOST_REQUIRE(mix_out_desc.second.get_child("outputs").size() == 16);
			}
			prior_attempt_unspent_outs_to_mix_outs = ret_tree.get_child(ret_json_key__send__prior_attempt_unspent_outs_to_mix_outs_new());
			size_t outs_to_mix_outs_count = 0;
			for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
			{
				++outs_to_mix_outs_count;
				string out_pub_key = outs_to_mix_outs_desc.first;
				cout << "bridge__transfers__send__sweepDust: pre_step2: output " << out_pub_key << endl;
				BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
			}
			BOOST_REQUIRE(outs_to_mix_outs_count == using_outs.size());
		}
		{
			boost::property_tree::ptree root;
			root.put("final_total_wo_fee", *final_total_wo_fee_string);
			root.put("change_amount", *change_amount_string); // from step1
			root.put("fee_amount", *using_fee_string); // from step1
			root.add_child("using_outs", using_outs); // from step1
			//
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("nettype_string", string_from_nettype(MAINNET));
			root.put("to_address_string", "4APbcAKxZ2KPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPPXmZxHN");
			root.put("from_address_string", "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
			root.put("sec_viewKey_string", "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
			root.put("sec_spendKey_string", "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
			root.put("fee_per_b", "666");
			root.put("fee_per_o", "100000");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("unlock_time", "0");
			root.put("priority", "1");
			root.add_child("mix_outs", mix_outs);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::send_step2__try_create_transaction(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			//
			tx_must_be_reconstructed = ret_tree.get<bool>("tx_must_be_reconstructed");
			cout << "bridge__transfers__send__sweepDust: step2: must tx be reconstructed? " << tx_must_be_reconstructed << endl;
			if (tx_must_be_reconstructed) {
				// declared outside the for-loop so that we can use it for subsequent iterations if needed:
				fee_actually_needed_string = ret_tree.get_optional<string>("fee_actually_needed");
				BOOST_REQUIRE(fee_actually_needed_string != none);
				BOOST_REQUIRE((*fee_actually_needed_string).size() > 0);
				//
				// This means we must go back through step1 to re-pick using_outs
				BOOST_REQUIRE(construction_attempt_n < 7); // not generally expecting to have to do this more than once or twice - i did see < 3 insufficient once so raised this
				continue; // proceed to next iteration (re-enter tx construction at step1(II) with fee_actually_needed_string from step2(I))
			}
			boost::optional<string> tx_hash = ret_tree.get_optional<string>("tx_hash");
			boost::optional<string> tx_key_string = ret_tree.get_optional<string>("tx_key");
			boost::optional<string> serialized_signed_tx = ret_tree.get_optional<string>("serialized_signed_tx");
			BOOST_REQUIRE(serialized_signed_tx != none);
			BOOST_REQUIRE((*serialized_signed_tx).size() > 0);
			cout << "bridge__transfers__send__sweepDust: serialized_signed_tx: " << *serialized_signed_tx << endl;
			BOOST_REQUIRE(tx_hash != none);
			BOOST_REQUIRE((*tx_hash).size() > 0);
			cout << "bridge__transfers__send__sweepDust: tx_hash: " << *tx_hash << endl;
			BOOST_REQUIRE(tx_key_string != none);
			BOOST_REQUIRE((*tx_key_string).size() > 0);
			cout << "bridge__transfers__send__sweepDust: tx_key_string: " << *tx_key_string << endl;
		}
	}
}
BOOST_AUTO_TEST_CASE(bridge__transfers__send__amountWOnlyDusty)
{
	using namespace serial_bridge;
	using namespace beldex_transfer_utils;
	//
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << DG_presweep__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	boost::property_tree::ptree unspent_outs = pt.get_child("unspent_outs");
	//
	boost::optional<string> mixin_string;
	boost::optional<string> change_amount_string;
	boost::optional<string> using_fee_string;
	boost::optional<string> final_total_wo_fee_string;
	boost::property_tree::ptree using_outs;
	boost::property_tree::ptree root;
	root.put("is_sweeping", "false");
	root.put("payment_id_string", "d2f602b240fbe624"); // optl
	root.put("sending_amount", "1000000");
	root.put("fee_per_b", "666");
	root.put("fee_per_o", "100000");
	root.put("fee_mask", "10000");
	root.put("fork_version", "16");
	root.put("priority", "1");
	root.add_child("unspent_outs", unspent_outs);

	auto ret_string = serial_bridge::send_step1__prepare_params_for_get_decoys(args_string_from_root(root));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
	BOOST_REQUIRE_MESSAGE(err_code == none, "Expected no error");
	BOOST_REQUIRE_MESSAGE(ret_tree.get<string>("using_fee") == string("39380000"), "Expected using_fee of 39380000");
	BOOST_REQUIRE_MESSAGE(ret_tree.get<string>("final_total_wo_fee") == string("1000000"), "Expected final_total_wo_fee of 1000000");
}
//string DG_postsweep__unspent_outs_json = "{\"unspent_outs\":[{\"amount\":\"3000000000\",\"public_key\":\"41be1978f58cabf69a9bed5b6cb3c8d588621ef9b67602328da42a213ee42271\",\"index\":1,\"global_index\":7611174,\"rct\":\"86a2c9f1f8e66848cd99bfda7a14d4ac6c3525d06947e21e4e55fe42a368507eb5b234ccdd70beca8b1fc8de4f2ceb1374e0f1fd8810849e7f11316c2cc063060008ffa5ac9827b776993468df21af8c963d12148622354f950cbe1369a92a0c\",\"tx_id\":5334971,\"tx_hash\":\"9d37c7fdeab91abfd1e7e120f5c49eac17b7ac04a97a0c93b51c172115df21ea\",\"tx_pub_key\":\"bd703d7f37995cc7071fb4d2929594b5e2a4c27d2b7c68a9064500ca7bc638b8\"}]}";
string DG_postsweep__unspent_outs_json = "{\"unspent_outs\": [{\"amount\": \"100000000\", \"public_key\": \"8b1e3ec8a3828f09845e3aec93b19c6788458df39b5045472739b896d7cb7c1b\", \"index\": 0, \"global_index\": 14205118, \"rct\": \"b746bda9aee02e971460efc3f9fe4243be305d724d2fb0ebbdc5f8abf31cdb909668123ad52a68f8\", \"tx_id\": 8225042, \"tx_hash\": \"ac8c1d9d89a289c7b2210c7cf94c5b03435b21e238557c2993246c1743c7cd5b\", \"tx_pub_key\": \"edc238c96cb30a739f56126ae962ac81be43e9aaa8a86313dec3d8ecfb36b7ef\", \"tx_prefix_hash\": \"293d3c03fdffa4e93600e51025287b37f1dc063a0cf22960d28f4ecf542aa516\", \"spend_key_images\": [\"d2d3db0a97ff7cde6774d2e8290559bf3e186e06783cb1ba39890bd31b0305ea\", \"44a97c766f23f1a471138fd1d5561b359f59c767498f829000cc8a17d6488abb\", \"73503ecb8c88eb6803df4f207901f9f57e847971d445bc232df13bb120c462d5\", \"5b6f0c36b6553ee3274037a37aaa7abdf4ad72900ce5ff588fe725652ab98665\", \"1d5447f30b261c8943d92289c80bb00973d363282fef06c086b2b660e88effae\", \"0b4b2e429aa59539de3ef6c55888307c6a6f6ea445c5f8e525a64a2f650ce5db\", \"0ff0bbaa87087449ae55d5df3a175050767c34b0186d53f8e64609b5af32d023\", \"070b01df752d5d9e4ffe54d587d3b63abcb3f7e73cec50047152c209f93372f7\", \"fddc4239b18fbe4232bec937ef5c1b399e7571ad720d6f527fccfe5c81d66c44\", \"0ecfa5b14b41473e368fc163f9b2e4f0118685d075edc01737bc75595cb20949\", \"8bbdf2254d173d77c1557b4d58e287eaca519d5d93a3b000062ebb423b1b59f5\", \"9ebc5f6db9c9d38ac3996ca98b7494dc3ab6c704134a3db845e54c54bc3510e9\", \"d8d7255ca9052b900bd738417b3ea49d0702c4865279ad888c4c4220ecd44f90\", \"5f57135e7f8c79b40c9d20eecd508409f594898c7369e205fed1e62a2be0fe6d\", \"1c8602ffbc7f1836425911d52c79a56f280c82c9ab9464a78bd9d1daa5a70ab3\"], \"height\": 2007212}]}";
//string DG_postsweep__rand_outs_json = "{\"mix_outs\":[{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"7453099\",\"public_key\":\"31f3a7fec0f6f09067e826b6c2904fd4b1684d7893dcf08c5b5d22e317e148bb\",\"rct\":\"ea6bcb193a25ce2787dd6abaaeef1ee0c924b323c6a5873db1406261e86145fc\"},{\"global_index\":\"7500097\",\"public_key\":\"f9d923500671da05a1bf44b932b872f0c4a3c88e6b3d4bf774c8be915e25f42b\",\"rct\":\"dcae4267a6c382bcd71fd1af4d2cbceb3749d576d7a3acc473dd579ea9231a52\"},{\"global_index\":\"7548483\",\"public_key\":\"839cbbb73685654b93e824c4843e745e8d5f7742e83494932307bf300641c480\",\"rct\":\"aa99d492f1d6f1b20dcd95b8fff8f67a219043d0d94b4551759016b4888573e7\"},{\"global_index\":\"7554755\",\"public_key\":\"b8860f0697988c8cefd7b4285fbb8bec463f136c2b9a9cadb3e57cebee10717f\",\"rct\":\"327f9b07bee9c4c25b5a990123cd2444228e5704ebe32016cd632866710279b5\"},{\"global_index\":\"7561477\",\"public_key\":\"561d734cb90bc4a64d49d37f85ea85575243e2ed749a3d6dcb4d27aa6bec6e88\",\"rct\":\"b5393e038df95b94bfda62b44a29141cac9e356127270af97193460d51949841\"},{\"global_index\":\"7567062\",\"public_key\":\"db1024ef67e7e73608ef8afab62f49e2402c8da3dc3197008e3ba720ad3c94a8\",\"rct\":\"1fedf95621881b77f823a70aa83ece26aef62974976d2b8cd87ed4862a4ec92c\"},{\"global_index\":\"7567508\",\"public_key\":\"6283f3cd2f050bba90276443fe04f6076ad2ad46a515bf07b84d424a3ba43d27\",\"rct\":\"10e16bb8a8b7b0c8a4b193467b010976b962809c9f3e6c047335dba09daa351f\"},{\"global_index\":\"7568716\",\"public_key\":\"7a7deb4eef81c1f5ce9cbd0552891cb19f1014a03a5863d549630824c7c7c0d3\",\"rct\":\"735d059dc3526334ac705ddc44c4316bb8805d2426dcea9544cde50cf6c7a850\"},{\"global_index\":\"7571196\",\"public_key\":\"535208e354cae530ed7ce752935e555d630cf2edd7f91525024ed9c332b2a347\",\"rct\":\"c3cf838faa14e993536c5581ca582fb0d96b70f713cf88f7f15c89336e5853ec\"},{\"global_index\":\"7571333\",\"public_key\":\"e73f27b7eb001aa7eac13df82814cda65b42ceeb6ef36227c25d5cbf82f6a5e4\",\"rct\":\"5f45f33c6800cdae202b37abe6d87b53d6873e7b30f3527161f44fa8db3104b6\"},{\"global_index\":\"7571335\",\"public_key\":\"fce982dbz8e7a6b71a1e632c7de8c5cbf54e8bacdfbf250f1ffc2a8d2f7055ce3\",\"rct\":\"407bdcc48e70eb3ef2cc22cefee6c6b5a3c59fd17bde12fda5f1a44a0fb39d14\"}]}]}";
string DG_postsweep__rand_outs_json = "{\"mix_outs\": [{\"amount\": \"0\", \"outputs\": [{\"global_index\": \"28513591\", \"public_key\": \"5e4130ea99d4dac0eb5f443815b30aa64ed095ee0fe07e1a1a77e182dbbb7a00\", \"rct\": \"4ca621e3eeac7b715c81fb84b27e8c13b5727a965e100aac117689645c90dfd3\"}, {\"global_index\": \"51118512\", \"public_key\": \"d8eee48083023bd5fdab6aa6b35a5c4016fafc61ab60df599955b08d342e8702\", \"rct\": \"0dbe511c8169601c235e18a661ac4d5416d79d3b61b2446956edbecf672461a6\"}, {\"global_index\": \"56822213\", \"public_key\": \"a3a7777ddfe482c57ecad71fe8a6932df0588de3fbe17177f5fc7311853d2ede\", \"rct\": \"27ab103d54a2ef240b6573c92a1ecb5e96faf51b8a3d0691d2986f570233d543\"}, {\"global_index\": \"58805284\", \"public_key\": \"2f235cbd5e8b8ea139ef7096560d9ebf7841a181c1dedc6f3b3fe2147394b046\", \"rct\": \"312fe9a54afbe3bb0d71dadc8f3d89b814bc74f4b561fa8c1618ee19d134d4bc\"}, {\"global_index\": \"60865089\", \"public_key\": \"4b887921c93ae44e6f0f951fc4356a2efbc219b13d05041d91f8e9a4f4085711\", \"rct\": \"5be1568e1250d92f629c3a9b677c89bd7cbf311065a23c44f5100552ad188e1f\"}, {\"global_index\": \"61244105\", \"public_key\": \"e239e15a556b5f27ece405e8c123f79a7d036486e785c91e9469160790ad73bc\", \"rct\": \"069f624249b84f6f61859408d72a806f8bf6bc2eee4ef42346b2ef5db897f1a5\"}, {\"global_index\": \"61459264\", \"public_key\": \"478e73f6f53da49ac68d023f6b2d2ee6cc4f01801ac3e16efc5b542ad1682aad\", \"rct\": \"39185efd7013bc4c023a8fb7cc64afd748554fa6856dfde185449d4d42e6eeb7\"}, {\"global_index\": \"61473472\", \"public_key\": \"db5e4325eaf97d0b668031673c82d7d28a601ce7b3841a8864fd73fb34ea0b5c\", \"rct\": \"30cf328e1a933993641fa04ce0c1802b6edaa3951c9f52ea0a1b83c10ccc2f13\"}, {\"global_index\": \"61487386\", \"public_key\": \"25126ff9b31a86b03755eaf153206908ac9724a50132797830403b70756d40fa\", \"rct\": \"be225025371608f5a9423916f822d5be8c6f13357e2952c7f42a1e5deddb99c5\"}, {\"global_index\": \"61533737\", \"public_key\": \"04d85ef8aefed7d9656b2fc1987c2a4f543ae2c3fd4408d4c4688426f1e7a27a\", \"rct\": \"90ef9e872e728d60830fb6b51bf252df87fe799abd06804a9218259cc5b560ac\"}, {\"global_index\": \"61562814\", \"public_key\": \"5a630464a8c792d17417cea00eeab5652092537a7ac4618afc8f1950b2def61a\", \"rct\": \"a148d68eb4ca9d6f3a4d62b9e20257fd49e59fa5eb443454d8d9a090019b2513\"}, {\"global_index\": \"61565384\", \"public_key\": \"a45918aadc54b01895daaf755fa3ac8992485968daddd1ccd191e64f5643f788\", \"rct\": \"4dc6823fe8562b2e97cc637f14e7d530c89fa5f602f4c178ad5cae8d0217eb56\"}, {\"global_index\": \"61567298\", \"public_key\": \"3c1dceb1cd027c6d6e71cf6b60bbd3b7a9e8adf63c4e82108a9d5a0bf5a05e62\", \"rct\": \"a91d89adc9c44625ecc8b25e54fc8efd1a74c50d1cddae3c5c8f4925d97d3c01\"}, {\"global_index\": \"61571915\", \"public_key\": \"c5b896dcee0c3374054c7200331764ef1a8049ccd5b951b40b25b110b4fa8eec\", \"rct\": \"0c5be57b392fc614c56ff763f29066d780c21b171e5b24f09e8eff605faf1972\"}, {\"global_index\": \"61594272\", \"public_key\": \"3462d1edc0748b4cca02a39b2a17616ac9b95aa2a8da2c66223473ed23162b1b\", \"rct\": \"ba510000414c954b3fcef528636879696eec29dcd755220c711794188779f872\"}, {\"global_index\": \"61595770\", \"public_key\": \"df99def4b61a2511221bae2010ebdf0f9789e798eea763e61046be230788ae52\", \"rct\": \"177b878f9bea0596467abae4921d5474065aadbc29c3813d387abd44e3817617\"}]}]}";

BOOST_AUTO_TEST_CASE(bridge__transfers__send__amount)
{
	using namespace serial_bridge;
	using namespace beldex_transfer_utils;
	//
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << DG_postsweep__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	boost::property_tree::ptree unspent_outs = pt.get_child("unspent_outs");
	boost::optional<boost::property_tree::ptree> prior_attempt_unspent_outs_to_mix_outs = none;
	//
	//
	// Send algorithm:
	bool tx_must_be_reconstructed = true; // for ease of writing this code, start this off true & structure whole thing as while loop
	boost::optional<string> fee_actually_needed_string = none;
	size_t construction_attempt_n = 0;
	while (tx_must_be_reconstructed) {
		construction_attempt_n += 1; // merely kept for assertion purposes
		//
		boost::optional<string> mixin_string;
		boost::optional<string> change_amount_string;
		boost::optional<string> using_fee_string;
		boost::optional<string> final_total_wo_fee_string;
		boost::property_tree::ptree using_outs;
		{
			boost::property_tree::ptree root;
			root.put("is_sweeping", "false");
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("sending_amount", "10000000");
			root.put("fee_per_b", "24658");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("priority", "1");
			root.add_child("unspent_outs", unspent_outs);
			if (fee_actually_needed_string != none) {
				BOOST_REQUIRE(construction_attempt_n > 1);
				BOOST_REQUIRE(prior_attempt_unspent_outs_to_mix_outs != none);
				//
				// for next round's integration - if it needs to re-enter... arg "prior_attempt_size_calcd_fee" and "prior_attempt_unspent_outs_to_mix_outs"
				root.put("prior_attempt_size_calcd_fee", *fee_actually_needed_string);
				for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
				{
					string out_pub_key = outs_to_mix_outs_desc.first;
					cout << "bridge__transfers__send__sweepDust: step1: prior output " << out_pub_key << endl;
					BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
				}
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			auto ret_string = serial_bridge::send_step1__prepare_params_for_get_decoys(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::ptree ret_tree;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				if ((CreateTransactionErrorCode)*err_code == beldex_transfer_utils::needMoreMoneyThanFound) {
					boost::optional<string> spendable_balance_string = ret_tree.get_optional<string>("spendable_balance");
					BOOST_REQUIRE(spendable_balance_string != none);
					BOOST_REQUIRE((*spendable_balance_string).size() > 0);
					//			uint64_t fee = stoull(*fee_string);
					//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send__amount: step1: needMoreMoneyThanFound: spendable_balance " << *spendable_balance_string << endl;
					//
					boost::optional<string> required_balance_string = ret_tree.get_optional<string>("required_balance");
					BOOST_REQUIRE(required_balance_string != none);
					BOOST_REQUIRE((*required_balance_string).size() > 0);
					//			uint64_t fee = stoull(*fee_string);
					//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send__amount: step1: needMoreMoneyThanFound: required_balance " << *required_balance_string << endl;
				}
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
				// ^--- not expecting anything like needMoreMoneyThanFound errors here
			}
			mixin_string = ret_tree.get_optional<string>("mixin");
			BOOST_REQUIRE(mixin_string != none);
			BOOST_REQUIRE((*mixin_string).size() > 0);
			uint64_t mixin = stoull(*mixin_string);
			BOOST_REQUIRE(mixin == 15);
			cout << "bridge__transfers__send__amount: mixin " << *mixin_string << endl;
			//
			using_fee_string = ret_tree.get_optional<string>("using_fee"); // save this
			BOOST_REQUIRE(using_fee_string != none);
			BOOST_REQUIRE((*using_fee_string).size() > 0);
			//		uint64_t using_fee = stoull(*using_fee_string);
			//	BOOST_REQUIRE(using_fee == 10); // TODO:?
			cout << "bridge__transfers__send__amount: step1: using_fee " << *using_fee_string << endl;
			//
			using_outs = ret_tree.get_child("using_outs"); // save this for step2
			for(boost::property_tree::ptree::value_type &output_desc : using_outs)
			{
				assert(output_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send__amount: step1: using_out " << output_desc.second.get<string>("public_key") << endl;
			}
			//
			change_amount_string = ret_tree.get_optional<string>("change_amount");
			BOOST_REQUIRE(change_amount_string != none);
			BOOST_REQUIRE((*change_amount_string).size() > 0);
			//		uint64_t change_amount = stoull(*change_amount_string);
			//	BOOST_REQUIRE(change_amount == 10); // TODO:?
			cout << "bridge__transfers__send__amount: step1: change_amount " << *change_amount_string << endl;
			//
			final_total_wo_fee_string = ret_tree.get_optional<string>("final_total_wo_fee");
			BOOST_REQUIRE(final_total_wo_fee_string != none);
			BOOST_REQUIRE((*final_total_wo_fee_string).size() > 0);
			//		uint64_t final_total_wo_fee = stoull(*final_total_wo_fee_string);
			//	BOOST_REQUIRE(final_total_wo_fee == 10); // TODO:?
			cout << "bridge__transfers__send__amount: step1: final_total_wo_fee " << *final_total_wo_fee_string << endl;
			//
		}
		boost::property_tree::ptree mix_outs;
		{
			boost::property_tree::ptree root;
			root.add_child("using_outs", using_outs); // from step1
			// NOTE: in the real algorithm you should request _previously unseen
			// mixouts from prior attempts each time pre_step2 must be called_
			// this being input as JSON merely for convenience
			boost::property_tree::ptree mix_outs_from_server;
			if (construction_attempt_n == 1)
			{
				boost::property_tree::ptree pt;
				stringstream ss;
				ss << DG_postsweep__rand_outs_json;
				boost::property_tree::json_parser::read_json(ss, pt);
				mix_outs_from_server = pt.get_child("mix_outs");
			}
			else
			{
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			root.add_child("mix_outs", mix_outs_from_server);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>(ret_json_key__any__err_code());
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			mix_outs = ret_tree.get_child(ret_json_key__send__mix_outs());
			BOOST_REQUIRE(mix_outs.size() == using_outs.size());
			for(boost::property_tree::ptree::value_type &mix_out_desc : mix_outs)
			{
				assert(mix_out_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send__amount: pre_step2: amount " << mix_out_desc.second.get<string>("amount") << endl;
				BOOST_REQUIRE(mix_out_desc.second.get_child("outputs").size() == 16);
			}
			prior_attempt_unspent_outs_to_mix_outs = ret_tree.get_child(ret_json_key__send__prior_attempt_unspent_outs_to_mix_outs_new());
			size_t outs_to_mix_outs_count = 0;
			for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
			{
				++outs_to_mix_outs_count;
				string out_pub_key = outs_to_mix_outs_desc.first;
				cout << "bridge__transfers__send__amount: pre_step2: output " << out_pub_key << endl;
				BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
			}
			BOOST_REQUIRE(outs_to_mix_outs_count == using_outs.size());
		}
		{
			boost::property_tree::ptree root;
			root.put("final_total_wo_fee", *final_total_wo_fee_string);
			cout << "change_amount_string: " << *change_amount_string << endl;
			root.put("change_amount", *change_amount_string); // from step1
			root.put("fee_amount", *using_fee_string); // from step1
			root.add_child("using_outs", using_outs); // from step1
			//
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("nettype_string", string_from_nettype(MAINNET));
			root.put("to_address_string", "4APbcAKxZ2KPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPPXmZxHN");
			root.put("from_address_string", "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
			root.put("sec_viewKey_string", "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
			root.put("sec_spendKey_string", "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
			root.put("fee_per_b", "666");
			root.put("fee_per_o", "100000");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("unlock_time", "0");
			root.put("priority", "1");
			root.add_child("mix_outs", mix_outs);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::send_step2__try_create_transaction(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			//
			tx_must_be_reconstructed = ret_tree.get<bool>("tx_must_be_reconstructed");
			cout << "bridge__transfers__send__amount: step2: must tx be reconstructed? " << tx_must_be_reconstructed << endl;
			if (tx_must_be_reconstructed) {
				// declared outside the for-loop so that we can use it for subsequent iterations if needed:
				fee_actually_needed_string = ret_tree.get_optional<string>("fee_actually_needed");
				BOOST_REQUIRE(fee_actually_needed_string != none);
				BOOST_REQUIRE((*fee_actually_needed_string).size() > 0);
				//
				// This means we must go back through step1 to re-pick using_outs
				BOOST_REQUIRE(construction_attempt_n < 3); // not generally expecting to have to do this more than once or twice
				continue; // proceed to next iteration (re-enter tx construction at step1(II) with fee_actually_needed_string from step2(I))
			}
			boost::optional<string> tx_hash = ret_tree.get_optional<string>("tx_hash");
			boost::optional<string> tx_key_string = ret_tree.get_optional<string>("tx_key");
			boost::optional<string> tx_pub_key_string = ret_tree.get_optional<string>("tx_pub_key");
			boost::optional<string> serialized_signed_tx = ret_tree.get_optional<string>("serialized_signed_tx");
			BOOST_REQUIRE(serialized_signed_tx != none);
			BOOST_REQUIRE((*serialized_signed_tx).size() > 0);
			cout << "bridge__transfers__send__amount: serialized_signed_tx: " << *serialized_signed_tx << endl;
			BOOST_REQUIRE(tx_hash != none);
			BOOST_REQUIRE((*tx_hash).size() > 0);
			cout << "bridge__transfers__send__amount: tx_hash: " << *tx_hash << endl;
			BOOST_REQUIRE(tx_key_string != none);
			BOOST_REQUIRE((*tx_key_string).size() > 0);
			cout << "bridge__transfers__send__amount: tx_key_string: " << *tx_key_string << endl;
			BOOST_REQUIRE(tx_pub_key_string != none);
			BOOST_REQUIRE((*tx_pub_key_string).size() > 0);
			cout << "bridge__transfers__send__amount: tx_pub_key_string: " << *tx_pub_key_string << endl;
		}
	}
}
//
BOOST_AUTO_TEST_CASE(bridged__decode_address)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("nettype_string", string_from_nettype(MAINNET));
	root.put("address", "4L6Gcy9TAHqPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPaL41VrjstLM5WevLZx");
	//
	auto ret_string = serial_bridge::decode_address(root.get<string>("address"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> pub_viewKey_string = ret_tree.get_optional<string>("publicViewKey");
	BOOST_REQUIRE(pub_viewKey_string != none);
	BOOST_REQUIRE((*pub_viewKey_string).size() > 0);
	cout << "bridged__decode_address: pub_viewKey_string: " << *pub_viewKey_string << endl;
	boost::optional<string> pub_spendKey_string = ret_tree.get_optional<string>("publicSpendKey");
	BOOST_REQUIRE(pub_spendKey_string != none);
	BOOST_REQUIRE((*pub_spendKey_string).size() > 0);
	cout << "bridged__decode_address: pub_spendKey_string: " << *pub_spendKey_string << endl;
	boost::optional<string> paymentID_string = ret_tree.get_optional<string>("paymentId");
	BOOST_REQUIRE(paymentID_string != none);
	BOOST_REQUIRE((*paymentID_string).size() > 0);
	cout << "bridged__decode_address: paymentID_string: " << *paymentID_string << endl;
	boost::optional<bool> isSubaddress = ret_tree.get_optional<bool>("isSubaddress");
	BOOST_REQUIRE(isSubaddress != none);
	BOOST_REQUIRE(*isSubaddress == false);
	cout << "bridged__decode_address: isSubaddress: " << *isSubaddress << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__is_subaddress)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("nettype_string", string_from_nettype(MAINNET));
	root.put("address", "4L6Gcy9TAHqPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPaL41VrjstLM5WevLZx");
	//
	bool value = serial_bridge::is_subaddress(root.get<string>("address"), root.get<string>("nettype_string"));
	BOOST_REQUIRE(value == false);
	cout << "bridged__is_subaddress: " << value << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__is_integrated_address)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("nettype_string", string_from_nettype(MAINNET));
	root.put("address", "4L6Gcy9TAHqPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPaL41VrjstLM5WevLZx");
	//
	bool value = serial_bridge::is_integrated_address(root.get<string>("address"), root.get<string>("nettype_string"));
	BOOST_REQUIRE(value == true);
	cout << "bridged__is_integrated_address: " << value << endl;
}

//
#include <boost/algorithm/string/predicate.hpp>
BOOST_AUTO_TEST_CASE(bridged__new_integrated_address)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("nettype_string", string_from_nettype(MAINNET));
	root.put("address", "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
	root.put("short_pid", "b79f8efc81f58f67");
	//
	string value = serial_bridge::new_integrated_address(root.get<string>("address"), root.get<string>("short_pid"), root.get<string>("nettype_string"));
	BOOST_REQUIRE((value).size() > 0);
	BOOST_REQUIRE(boost::equal(value, string("4DhdwdSDgoS9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqmCzkMP1DMV6WCiNCdsp")));
	cout << "bridged__new_integrated_address: " << value << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__new_short_payment_id)
{
	using namespace serial_bridge;
	//
	string value = serial_bridge::new_payment_id();
	BOOST_REQUIRE((value).size() > 0);
	cout << "bridged__new_short_payment_id: " << value << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__new_wallet)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("nettype_string", string_from_nettype(MAINNET));
	root.put("locale_language_code", "en-US");
	//
	auto ret_string = serial_bridge::newly_created_wallet(root.get<string>("locale_language_code"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> mnemonic_string = ret_tree.get_optional<string>("mnemonic");
	BOOST_REQUIRE(mnemonic_string != none);
	BOOST_REQUIRE((*mnemonic_string).size() > 0);
	cout << "bridged__new_wallet: mnemonic: " << *mnemonic_string << endl;
	boost::optional<string> mnemonic_language = ret_tree.get_optional<string>("mnemonicLanguage");
	BOOST_REQUIRE(mnemonic_language != none);
	BOOST_REQUIRE((*mnemonic_language).size() > 0);
	cout << "bridged__new_wallet: mnemonic_language: " << *mnemonic_language << endl;
	boost::optional<string> sec_seed_string = ret_tree.get_optional<string>("seed");
	BOOST_REQUIRE(sec_seed_string != none);
	BOOST_REQUIRE((*sec_seed_string).size() > 0);
	cout << "bridged__new_wallet: sec_seed: " << *sec_seed_string << endl;
	boost::optional<string> address_string = ret_tree.get_optional<string>("address");
	BOOST_REQUIRE(address_string != none);
	BOOST_REQUIRE((*address_string).size() > 0);
	cout << "bridged__new_wallet: address: " << *address_string << endl;
	boost::optional<string> pub_viewKey_string = ret_tree.get_optional<string>("publicViewKey");
	BOOST_REQUIRE(pub_viewKey_string != none);
	BOOST_REQUIRE((*pub_viewKey_string).size() > 0);
	cout << "bridged__new_wallet: pub_viewKey_string: " << *pub_viewKey_string << endl;
	boost::optional<string> pub_spendKey_string = ret_tree.get_optional<string>("publicSpendKey");
	BOOST_REQUIRE(pub_spendKey_string != none);
	BOOST_REQUIRE((*pub_spendKey_string).size() > 0);
	cout << "bridged__new_wallet: pub_spendKey_string: " << *pub_spendKey_string << endl;
	boost::optional<string> sec_viewKey_string = ret_tree.get_optional<string>("privateViewKey");
	BOOST_REQUIRE(sec_viewKey_string != none);
	BOOST_REQUIRE((*sec_viewKey_string).size() > 0);
	cout << "bridged__new_wallet: sec_viewKey_string: " << *sec_viewKey_string << endl;
	boost::optional<string> sec_spendKey_string = ret_tree.get_optional<string>("privateSpendKey");
	BOOST_REQUIRE(sec_spendKey_string != none);
	BOOST_REQUIRE((*sec_spendKey_string).size() > 0);
	cout << "bridged__new_wallet: sec_spendKey_string: " << *sec_spendKey_string << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__are_equal_mnemonics)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("a", "foxe selfish hum nexus juven dodeg pepp ember biscuti elap jazz vibrate biscui");
	root.put("b", "fox sel hum nex juv\r  \ndod pep emb bis ela jaz vib bis");
	//
	bool value  = serial_bridge::are_equal_mnemonics(root.get<string>("a"), root.get<string>("b"));
	BOOST_REQUIRE(value != false);
	cout << "bridged__are_equal_mnemonics: " << value << endl;
}
BOOST_AUTO_TEST_CASE(bridged__are_equal_mnemonics__caps)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("a", "Neubau umarmen Abart umarmen Turban feilen Brett Bargeld Episode Milchkuh Substanz Jahr Armband Maibaum Tand Grünalge Tabak erziehen Federboa Lobrede Tenor Leuchter Curry Diskurs Tenor");
			 root.put("b", "neubau umarm Abart umarmen Turban feilen Brett Bargel Epis Milchkuh Subst Jahr Armband Maib Tand Grüna Tabak erzie Feder Lobre Tenor Leuch Curry Diskurs tenor");
	//
	bool value = serial_bridge::are_equal_mnemonics(root.get<string>("a"), root.get<string>("b"));
	BOOST_REQUIRE(value != false);
	cout << "bridged__are_equal_mnemonics__caps: " << value << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__mnemonic_from_seed)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("seed_string", "9c973aa296b79bbf452781dd3d32ad7f");
	root.put("wordset_name", "English");
	//
	auto ret_string = serial_bridge::mnemonic_from_seed(root.get<string>("seed_string"), root.get<string>("wordset_name"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> mnemonic_string = ret_tree.get_optional<string>("retVal");
	BOOST_REQUIRE(mnemonic_string != none);
	BOOST_REQUIRE((*mnemonic_string).size() > 0);
	cout << "bridged__mnemonic_from_seed: mnemonic: " << *mnemonic_string << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__seed_and_keys_from_mnemonic)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("mnemonic_string", "foxe selfish\n\r \t     hum nexus juven dodeg pepp \r\n\r\n ember biscuti elap jazz vibrate biscui");
	root.put("nettype_string", string_from_nettype(MAINNET));
	//
	auto ret_string = serial_bridge::seed_and_keys_from_mnemonic(root.get<string>("mnemonic_string"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> mnemonic_language = ret_tree.get_optional<string>("mnemonicLanguage");
	BOOST_REQUIRE(mnemonic_language != none);
	BOOST_REQUIRE((*mnemonic_language).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: mnemonic_language: " << *mnemonic_language << endl;
	boost::optional<string> sec_seed_string = ret_tree.get_optional<string>("seed");
	BOOST_REQUIRE(sec_seed_string != none);
	BOOST_REQUIRE((*sec_seed_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: sec_seed: " << *sec_seed_string << endl;
	boost::optional<string> address_string = ret_tree.get_optional<string>("address");
	BOOST_REQUIRE(address_string != none);
	BOOST_REQUIRE((*address_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: address: " << *address_string << endl;
	BOOST_REQUIRE((*address_string) == "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
	boost::optional<string> pub_viewKey_string = ret_tree.get_optional<string>("publicViewKey");
	BOOST_REQUIRE(pub_viewKey_string != none);
	BOOST_REQUIRE((*pub_viewKey_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: pub_viewKey_string: " << *pub_viewKey_string << endl;
	boost::optional<string> pub_spendKey_string = ret_tree.get_optional<string>("publicSpendKey");
	BOOST_REQUIRE(pub_spendKey_string != none);
	BOOST_REQUIRE((*pub_spendKey_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: pub_spendKey_string: " << *pub_spendKey_string << endl;
	boost::optional<string> sec_viewKey_string = ret_tree.get_optional<string>("privateViewKey");
	BOOST_REQUIRE(sec_viewKey_string != none);
	BOOST_REQUIRE((*sec_viewKey_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: sec_viewKey_string: " << *sec_viewKey_string << endl;
	boost::optional<string> sec_spendKey_string = ret_tree.get_optional<string>("privateSpendKey");
	BOOST_REQUIRE(sec_spendKey_string != none);
	BOOST_REQUIRE((*sec_spendKey_string).size() > 0);
	cout << "bridged__seed_and_keys_from_mnemonic: sec_spendKey_string: " << *sec_spendKey_string << endl;
}
BOOST_AUTO_TEST_CASE(bridged__validate_components_for_login__subaddress)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("address_string", "852t3x5nfQ7PLnavxP1Q6S2ff18tvy8Cih4ikkd61aqd2BV5iTaeY6PFBeLPcHZdrvfumGJx9z1Md6fwyxKSykyHKJAMrk6");
	root.put("sec_viewKey_string", "…");
	root.put("sec_spendKey_string", "…");
	root.put("seed_string", "…");
	root.put("nettype_string", string_from_nettype(MAINNET));
	//
	auto ret_string = serial_bridge::validate_components_for_login(root.get<string>("address_string"), root.get<string>("sec_viewKey_string"), root.get<string>("sec_spendKey_string"), root.get<string>("seed_string"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	BOOST_REQUIRE(err_string != none);
	BOOST_REQUIRE((*err_string).compare("Can't log in with a sub-address") == 0);
	boost::optional<bool> isValid = ret_tree.get_optional<bool>("isValid");
	BOOST_REQUIRE(isValid == none || *isValid == false);
}
BOOST_AUTO_TEST_CASE(bridged__validate_components_for_login)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("address_string", "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
	root.put("sec_viewKey_string", "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
	root.put("sec_spendKey_string", "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
	root.put("seed_string", "9c973aa296b79bbf452781dd3d32ad7f");
	root.put("nettype_string", string_from_nettype(MAINNET));
	//
	auto ret_string = serial_bridge::validate_components_for_login(root.get<string>("address_string"), root.get<string>("sec_viewKey_string"), root.get<string>("sec_spendKey_string"), root.get<string>("seed_string"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<bool> isValid = ret_tree.get_optional<bool>("isValid");
	BOOST_REQUIRE(isValid == true);
	cout << "bridged__validate_components_for_login: isValid: " << isValid << endl;
	boost::optional<bool> isInViewOnlyMode = ret_tree.get_optional<bool>("isViewOnly");
	BOOST_REQUIRE(isInViewOnlyMode == false);
	cout << "bridged__validate_components_for_login: isInViewOnlyMode: " << isInViewOnlyMode << endl;
	boost::optional<string> pub_viewKey_string = ret_tree.get_optional<string>("publicViewKey");
	BOOST_REQUIRE(pub_viewKey_string != none);
	BOOST_REQUIRE((*pub_viewKey_string).size() > 0);
	cout << "bridged__validate_components_for_login: pub_viewKey_string: " << *pub_viewKey_string << endl;
	boost::optional<string> pub_spendKey_string = ret_tree.get_optional<string>("publicSpendKey");
	BOOST_REQUIRE(pub_spendKey_string != none);
	BOOST_REQUIRE((*pub_spendKey_string).size() > 0);
	cout << "bridged__validate_components_for_login: pub_spendKey_string: " << *pub_spendKey_string << endl;
}
BOOST_AUTO_TEST_CASE(bridged__estimated_tx_network_fee)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("fee_per_b", "666");
	root.put("fee_per_o", "100000");
	root.put("fork_version", "17");
	root.put("priority", "2");
	//
	auto ret_string = serial_bridge::estimated_tx_network_fee(root.get<string>("priority"), root.get<string>("fee_per_b"),root.get<string>("fee_per_o"), root.get<string>("fork_version"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> fee_string = ret_tree.get_optional<string>("retVal");
	BOOST_REQUIRE(fee_string != none);
	BOOST_REQUIRE((*fee_string).size() > 0);
	uint64_t fee = stoull(*fee_string);
	BOOST_REQUIRE(fee == 279251850);
	cout << "bridged__estimated_tx_network_fee: " << fee << endl;
}

BOOST_AUTO_TEST_CASE(bridged__generate_key_image)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("sec_viewKey_string", "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
	root.put("sec_spendKey_string", "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
	root.put("pub_spendKey_string", "3eb884d3440d71326e27cc07a861b873e72abd339feb654660c36a008a0028b3");
	root.put("tx_pub_key", "fc7f85bf64c6e4f6aa612dbc8ddb1bb77a9283656e9c2b9e777c9519798622b2");
	root.put("out_index", "0");
	//
	auto ret_string = serial_bridge::generate_key_image(root.get<string>("tx_pub_key"), root.get<string>("sec_viewKey_string"), root.get<string>("pub_spendKey_string"), root.get<string>("sec_spendKey_string"), root.get<string>("out_index"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> key_image_string = ret_tree.get_optional<string>("retVal");
	BOOST_REQUIRE(key_image_string != none);
	BOOST_REQUIRE((*key_image_string).size() > 0);
	BOOST_REQUIRE(*key_image_string == "ae30ee23051dc0bdf10303fbd3b7d8035a958079eb66516b1740f2c9b02c804e");
	cout << "bridged__generate_key_image: " << *key_image_string << endl;
}
//
BOOST_AUTO_TEST_CASE(bridged__address_and_keys_from_seed)
{
	using namespace serial_bridge;
	//
	boost::property_tree::ptree root;
	root.put("seed_string", "9c973aa296b79bbf452781dd3d32ad7f");
	root.put("nettype_string", string_from_nettype(MAINNET));
	//
	auto ret_string = serial_bridge::address_and_keys_from_seed(root.get<string>("seed_string"), root.get<string>("nettype_string"));
	stringstream ret_stream;
	ret_stream << ret_string;
	boost::property_tree::ptree ret_tree;
	boost::property_tree::read_json(ret_stream, ret_tree);
	boost::optional<string> err_string = ret_tree.get_optional<string>("err_msg");
	if (err_string != none) {
		BOOST_REQUIRE_MESSAGE(false, *err_string);
	}
	boost::optional<string> address_string = ret_tree.get_optional<string>("address");
	BOOST_REQUIRE(address_string != none);
	BOOST_REQUIRE((*address_string).size() > 0);
	cout << "bridged__address_and_keys_from_seed: address: " << *address_string << endl;
	BOOST_REQUIRE(*address_string == "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
	boost::optional<string> pub_viewKey_string = ret_tree.get_optional<string>("publicViewKey");
	BOOST_REQUIRE(pub_viewKey_string != none);
	BOOST_REQUIRE((*pub_viewKey_string).size() > 0);
	cout << "bridged__address_and_keys_from_seed: pub_viewKey_string: " << *pub_viewKey_string << endl;
	boost::optional<string> pub_spendKey_string = ret_tree.get_optional<string>("publicSpendKey");
	BOOST_REQUIRE(pub_spendKey_string != none);
	BOOST_REQUIRE((*pub_spendKey_string).size() > 0);
	cout << "bridged__address_and_keys_from_seed: pub_spendKey_string: " << *pub_spendKey_string << endl;
	boost::optional<string> sec_viewKey_string = ret_tree.get_optional<string>("privateViewKey");
	BOOST_REQUIRE(sec_viewKey_string != none);
	BOOST_REQUIRE((*sec_viewKey_string).size() > 0);
	BOOST_REQUIRE(*sec_viewKey_string == "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
	cout << "bridged__address_and_keys_from_seed: sec_viewKey_string: " << *sec_viewKey_string << endl;
	boost::optional<string> sec_spendKey_string = ret_tree.get_optional<string>("privateSpendKey");
	BOOST_REQUIRE(sec_spendKey_string != none);
	BOOST_REQUIRE((*sec_spendKey_string).size() > 0);
	BOOST_REQUIRE(*sec_spendKey_string == "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
	cout << "bridged__address_and_keys_from_seed: sec_spendKey_string: " << *sec_spendKey_string << endl;
}


string OM_stagenet__unspent_outs_json = "{\"unspent_outs\": [{\"amount\": \"19899476090000\", \"public_key\": \"583df927727f46fed3d3471b803aa4ee71f615d1a34dba28fd821c811f10dfe1\", \"index\": 1, \"global_index\": 3158595, \"rct\": \"b4a6ac9c02db5f6c5853bb01e83e7ec2999dbb6079c85c954b57f2093fe6e7fce20c7176efd61858\", \"tx_id\": 1286324, \"tx_hash\": \"698f4686fff9f1ab65b1bffef317a602ee0384992787df5817a8281089d9c433\", \"tx_pub_key\": \"fc0bcbe33325cf68706e912088b474e4709c38aaffdab82aed2af620cc2c0cf2\", \"tx_prefix_hash\": \"2b50c5acd71deeef421f4975b485633a80a3ec5e35d42eae15d894eef0d044c5\", \"spend_key_images\": [\"4bbb8eec3520eab7ec27562ca4b46b94b17405e406dc6e62fcb930396b8ea317\", \"8f62600412ad25e07287417d3534eca2bdcf3bfa7d3e2e1705daec66942b7118\", \"3a6554ac27e1fa83bcfd5d03b6873bf2dc39e580fca31f7f55a11558eb778002\", \"27112843b72aeacd0fa8f66a1f547f2f7385e24511b9e3cc46c024ba2524b6fe\", \"b79094b611f31785677e700e10795d53c6f9a09421fe3b3457a24d348b68b54e\", \"c44e4468aa4ffe95b6f859c8485211917becfc3a7e76f027180e340826831cdb\", \"eda9004d7fc56e56627b66481e5abb4cfb01fdf62388d1f920066202e025f5b4\", \"df04d494e251791f9ff7a113883f8e0c9a550326558ca92f2b95e47180b7f918\"], \"height\": 791498}]}";


string OM_stagenet__rand_outs_json = "{\"mix_outs\": [{\"amount\": \"0\", \"outputs\": [{\"global_index\": \"6081880\", \"public_key\": \"278a7fb76b9d2f57f219447b7f86e6b3566afd42949dd0f72a3af71c156d8825\", \"rct\": \"f80c130598de33a098a1b18b8f5845596f84718d5b53ed2afc034250dd3b746b\"}, {\"global_index\": \"6088776\", \"public_key\": \"301af56c8af3365c29902be757c958b65a834c270dad018c1ddd4851e4d5819e\", \"rct\": \"a1d42807010b07bca843c068e3dade17b147424b3a417dd2bf2e07d21eea8e56\"}, {\"global_index\": \"6088817\", \"public_key\": \"39fd361fa9481046a7a1ffe3adbda16376af0fce0ce5c35d46aa769a6cdd8a8e\", \"rct\": \"642a3b694b040b464d03d536c12662c93b6168781d20e0b89add372b83bbca67\"}, {\"global_index\": \"6098077\", \"public_key\": \"df8f2e03a2f7dcf82192bbab6f19b0a7b44920fa5b0518d618c709ce7d2b87e2\", \"rct\": \"187805247627b375b5f93735ea97932405f19caeac2218027cae921591887b95\"}, {\"global_index\": \"6107024\", \"public_key\": \"1db3bd162f05b0ff62202feae4f41b7c7b9ddcd1ae87764ca221d7f69b1ba7d3\", \"rct\": \"df988cc5bbd0186cf977d80b2cad03ef92e62d31ca93c8a1ab4041dee74d7245\"}, {\"global_index\": \"6116945\", \"public_key\": \"60fc589666a1ee3b6784525c149ede123841c572548d212bc1e3655786d716dd\", \"rct\": \"1d7251a785760df85b65acc8a48dc1c588076b4b822c59d009cc6e3f3e81f1ab\"}, {\"global_index\": \"6126942\", \"public_key\": \"464849ffc9a16896c59b952d35cba2e3906eae3493ed15a6d7aa8774c9c12b37\", \"rct\": \"2ecb1badae63e0c1609d21523238233522264164aca1cdd0de0840cb2ebd3b71\"}, {\"global_index\": \"6128547\", \"public_key\": \"ec047a50ce90151d075933dccb01a6ce7230c5e05758b16025a66ef87d5da8cf\", \"rct\": \"7e87ebb1a7fb7d80f1ee257e9ccdfa68b3f1123df7ea3c874e4648ef88870975\"}, {\"global_index\": \"6130416\", \"public_key\": \"8a48d9267937b55445d70a104b67a2563fe1aa378b8073fdaef057767bebeef8\", \"rct\": \"855c1c74d638d78e252013ecd2a615440efd3a6f32f6aa2e5135d96e9abc7386\"}, {\"global_index\": \"6133652\", \"public_key\": \"cedf64a5fe7323e3dc2698e00644e90186426349c8258509b43b48371b8444a1\", \"rct\": \"64a9d8700371bbd0938c682b07fbddf2f6d1248f7f16eacad739b8547649c5b8\"}, {\"global_index\": \"6134071\", \"public_key\": \"c02fad190544129da1a1595bccf912921c7058d51b69468bfd8a270d387845b2\", \"rct\": \"cf715a9734def52e3182ec5692676fd8969e9ab3719086794a25ca0dc029b351\"}, {\"global_index\": \"6134452\", \"public_key\": \"9cddb03f1e5b44b920ca236689fb1bee3617ee6d25e85ee3734d13794578b64e\", \"rct\": \"5d1d9870458f64f1d2bed04c205597d7705dd815b33247d8905d303347518add\"}, {\"global_index\": \"6134767\", \"public_key\": \"f884a1e87dd11e2ca6b58a9096ccda0d6fbfca7aa2c8078b1e7c1eeb2c335ac3\", \"rct\": \"c0b829211a7185f3a8dcb8c251a99cfa97c9ea33f4483b54eaddd6d42528de26\"}, {\"global_index\": \"6135720\", \"public_key\": \"341f0d59972ae3de145dbe99905984b9b03f20d4197ccae25c055d6e8e8414c8\", \"rct\": \"fab7ef49dd00986ba326c802c2a2658eb8af0b5bd6b543e20ea3f4354b078915\"}, {\"global_index\": \"6135853\", \"public_key\": \"f2eec91195054a005bb45d0ac72c46ad4cf5fbbb55db94d37f1204690c2f0660\", \"rct\": \"f27d01312ad49ccbeddd2239c738a88c267177e6f1c0e35dd86d99ff9b1d1b3f\"}, {\"global_index\": \"6134581\", \"public_key\": \"e8dfd3c3127b12fda7404f050633e8eedcdd8bbd6b415b708a63c32070a7ccc9\", \"rct\": \"36b7b8affa8d6e4e105175de538b506cbab21b03c93ed4e75c1a42c821464b7a\"}]}]}";




BOOST_AUTO_TEST_CASE(bridge__transfers__send_stagenet_coinbase)
{
	using namespace serial_bridge;
	using namespace beldex_transfer_utils;
	//
	// this being input as JSON merely for convenience
	boost::property_tree::ptree pt;
	stringstream ss;
	ss << OM_stagenet__unspent_outs_json;
	boost::property_tree::json_parser::read_json(ss, pt);
	boost::property_tree::ptree unspent_outs = pt.get_child("unspent_outs");
	boost::optional<boost::property_tree::ptree> prior_attempt_unspent_outs_to_mix_outs = none;
	//
	//
	// Send algorithm:
	bool tx_must_be_reconstructed = true; // for ease of writing this code, start this off true & structure whole thing as while loop
	boost::optional<string> fee_actually_needed_string = none;
	size_t construction_attempt_n = 0;
	while (tx_must_be_reconstructed) {
		construction_attempt_n += 1; // merely kept for assertion purposes
		//
		boost::optional<string> mixin_string;
		boost::optional<string> change_amount_string;
		boost::optional<string> using_fee_string;
		boost::optional<string> final_total_wo_fee_string;
		boost::property_tree::ptree using_outs;
		{
			boost::property_tree::ptree root;
			root.put("is_sweeping", "false");
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("sending_amount", "1000000000000");
			root.put("fee_per_b", "666");
			root.put("fee_per_o", "100000");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("priority", "1");
			root.add_child("unspent_outs", unspent_outs);
			if (fee_actually_needed_string != none) {
				BOOST_REQUIRE(construction_attempt_n > 1);
				BOOST_REQUIRE(prior_attempt_unspent_outs_to_mix_outs != none);
				//
				// for next round's integration - if it needs to re-enter... arg "prior_attempt_size_calcd_fee" and "prior_attempt_unspent_outs_to_mix_outs"
				root.put("prior_attempt_size_calcd_fee", *fee_actually_needed_string);
				for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
				{
					string out_pub_key = outs_to_mix_outs_desc.first;
					cout << "bridge__transfers__send__sweepDust: step1: prior output " << out_pub_key << endl;
					BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
				}
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			auto ret_string = serial_bridge::send_step1__prepare_params_for_get_decoys(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::ptree ret_tree;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				if ((CreateTransactionErrorCode)*err_code == beldex_transfer_utils::needMoreMoneyThanFound) {
					boost::optional<string> spendable_balance_string = ret_tree.get_optional<string>("spendable_balance");
					BOOST_REQUIRE(spendable_balance_string != none);
					BOOST_REQUIRE((*spendable_balance_string).size() > 0);
					//			uint64_t fee = stoull(*fee_string);
					//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send_stagenet_coinbase: step1: needMoreMoneyThanFound: spendable_balance " << *spendable_balance_string << endl;
					//
					boost::optional<string> required_balance_string = ret_tree.get_optional<string>("required_balance");
					BOOST_REQUIRE(required_balance_string != none);
					BOOST_REQUIRE((*required_balance_string).size() > 0);
					//			uint64_t fee = stoull(*fee_string);
					//			BOOST_REQUIRE(fee == 135000000);
					cout << "bridge__transfers__send_stagenet_coinbase: step1: needMoreMoneyThanFound: required_balance " << *required_balance_string << endl;
				}
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
				// ^--- not expecting anything like needMoreMoneyThanFound errors here
			}
			mixin_string = ret_tree.get_optional<string>("mixin");
			BOOST_REQUIRE(mixin_string != none);
			BOOST_REQUIRE((*mixin_string).size() > 0);
			uint64_t mixin = stoull(*mixin_string);
			BOOST_REQUIRE(mixin == 15);
			cout << "bridge__transfers__send_stagenet_coinbase: mixin " << *mixin_string << endl;
			//
			using_fee_string = ret_tree.get_optional<string>("using_fee"); // save this
			BOOST_REQUIRE(using_fee_string != none);
			BOOST_REQUIRE((*using_fee_string).size() > 0);
			//		uint64_t using_fee = stoull(*using_fee_string);
			//	BOOST_REQUIRE(using_fee == 10); // TODO:?
			cout << "bridge__transfers__send_stagenet_coinbase: step1: using_fee " << *using_fee_string << endl;
			//
			using_outs = ret_tree.get_child("using_outs"); // save this for step2
			for(boost::property_tree::ptree::value_type &output_desc : using_outs)
			{
				assert(output_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send_stagenet_coinbase: step1: using_out " << output_desc.second.get<string>("public_key") << endl;
			}
			//
			change_amount_string = ret_tree.get_optional<string>("change_amount");
			BOOST_REQUIRE(change_amount_string != none);
			BOOST_REQUIRE((*change_amount_string).size() > 0);
			//		uint64_t change_amount = stoull(*change_amount_string);
			//	BOOST_REQUIRE(change_amount == 10); // TODO:?
			cout << "bridge__transfers__send_stagenet_coinbase: step1: change_amount " << *change_amount_string << endl;
			//
			final_total_wo_fee_string = ret_tree.get_optional<string>("final_total_wo_fee");
			BOOST_REQUIRE(final_total_wo_fee_string != none);
			BOOST_REQUIRE((*final_total_wo_fee_string).size() > 0);
			//		uint64_t final_total_wo_fee = stoull(*final_total_wo_fee_string);
			//	BOOST_REQUIRE(final_total_wo_fee == 10); // TODO:?
			cout << "bridge__transfers__send_stagenet_coinbase: step1: final_total_wo_fee " << *final_total_wo_fee_string << endl;
			//
		}
		boost::property_tree::ptree mix_outs;
		{
			boost::property_tree::ptree root;
			root.add_child("using_outs", using_outs); // from step1
			// NOTE: in the real algorithm you should request _previously unseen
			// mixouts from prior attempts each time pre_step2 must be called_
			// this being input as JSON merely for convenience
			boost::property_tree::ptree mix_outs_from_server;
			if (construction_attempt_n == 1)
			{
				boost::property_tree::ptree pt;
				stringstream ss;
				ss << DG_postsweep__rand_outs_json;
				boost::property_tree::json_parser::read_json(ss, pt);
				mix_outs_from_server = pt.get_child("mix_outs");
			}
			else
			{
				root.add_child("prior_attempt_unspent_outs_to_mix_outs", *prior_attempt_unspent_outs_to_mix_outs);
			}
			root.add_child("mix_outs", mix_outs_from_server);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::pre_step2_tie_unspent_outs_to_mix_outs_for_all_future_tx_attempts(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>(ret_json_key__any__err_code());
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			mix_outs = ret_tree.get_child(ret_json_key__send__mix_outs());
			BOOST_REQUIRE(mix_outs.size() == using_outs.size());
			for(boost::property_tree::ptree::value_type &mix_out_desc : mix_outs)
			{
				assert(mix_out_desc.first.empty()); // array elements have no names
				cout << "bridge__transfers__send__amount: pre_step2: amount " << mix_out_desc.second.get<string>("amount") << endl;
				BOOST_REQUIRE(mix_out_desc.second.get_child("outputs").size() == 16);
			}
			prior_attempt_unspent_outs_to_mix_outs = ret_tree.get_child(ret_json_key__send__prior_attempt_unspent_outs_to_mix_outs_new());
			size_t outs_to_mix_outs_count = 0;
			for(boost::property_tree::ptree::value_type &outs_to_mix_outs_desc : *prior_attempt_unspent_outs_to_mix_outs)
			{
				++outs_to_mix_outs_count;
				string out_pub_key = outs_to_mix_outs_desc.first;
				cout << "bridge__transfers__send__amount: pre_step2: output " << out_pub_key << endl;
				BOOST_REQUIRE(outs_to_mix_outs_desc.second.size() == 16);
			}
			BOOST_REQUIRE(outs_to_mix_outs_count == using_outs.size());
		}
		{
			boost::property_tree::ptree root;
			root.put("final_total_wo_fee", *final_total_wo_fee_string);
			root.put("change_amount", *change_amount_string); // from step1
			root.put("fee_amount", *using_fee_string); // from step1
			root.add_child("using_outs", using_outs); // from step1
			//
			root.put("payment_id_string", "d2f602b240fbe624"); // optl
			root.put("nettype_string", string_from_nettype(DEVNET));
			root.put("to_address_string", "57Hx8QpLUSMjhgoCNkvJ2Ch91mVyxcffESCprnRPrtbphMCv8iGUEfCUJxrpUWUeWrS9vPWnFrnMmTwnFpSKJrSKNuaXc5q");
			root.put("from_address_string", "56bY2v2RJZNEvrKdYuwG73Q2idshQyGc5fV74BZqoVv72MPSBEakPbfWYtQH4PLGhk3uaCjNZ81XJ7o9pimAXzQFCv7bxxf");
			root.put("sec_viewKey_string", "9ef8e116d2c774b207a2dd6a234dab8f5d54becc04aa26ccbd6f1f67e8427308");
			root.put("sec_spendKey_string", "4acde2a96d5085423fcc8713c878448b35e45900f4e9cf2c0b643eb4268e140e");
			root.put("fee_per_b", "166333");
			root.put("fee_mask", "10000");
			root.put("fork_version", "16");
			root.put("unlock_time", "0");
			root.put("priority", "1");
			root.add_child("mix_outs", mix_outs);
			//
			boost::property_tree::ptree ret_tree;
			auto ret_string = serial_bridge::send_step2__try_create_transaction(args_string_from_root(root));
			stringstream ret_stream;
			ret_stream << ret_string;
			boost::property_tree::read_json(ret_stream, ret_tree);
			boost::optional<uint32_t> err_code = ret_tree.get_optional<uint32_t>("err_code");
			if (err_code != none && (CreateTransactionErrorCode)*err_code != beldex_transfer_utils::noError) {
				auto err_msg = err_msg_from_err_code__create_transaction((CreateTransactionErrorCode)*err_code);
				BOOST_REQUIRE_MESSAGE(false, err_msg);
			}
			//
			tx_must_be_reconstructed = ret_tree.get<bool>("tx_must_be_reconstructed");
			cout << "bridge__transfers__send_stagenet_coinbase: step2: must tx be reconstructed? " << tx_must_be_reconstructed << endl;
			if (tx_must_be_reconstructed) {
				// declared outside the for-loop so that we can use it for subsequent iterations if needed:
				fee_actually_needed_string = ret_tree.get_optional<string>("fee_actually_needed");
				BOOST_REQUIRE(fee_actually_needed_string != none);
				BOOST_REQUIRE((*fee_actually_needed_string).size() > 0);
				//
				// This means we must go back through step1 to re-pick using_outs
				BOOST_REQUIRE(construction_attempt_n < 3); // not generally expecting to have to do this more than once or twice
				continue; // proceed to next iteration (re-enter tx construction at step1(II) with fee_actually_needed_string from step2(I))
			}
			boost::optional<string> tx_hash = ret_tree.get_optional<string>("tx_hash");
			boost::optional<string> tx_key_string = ret_tree.get_optional<string>("tx_key");
			boost::optional<string> serialized_signed_tx = ret_tree.get_optional<string>("serialized_signed_tx");
			BOOST_REQUIRE(serialized_signed_tx != none);
			BOOST_REQUIRE((*serialized_signed_tx).size() > 0);
			cout << "bridge__transfers__send_stagenet_coinbase: serialized_signed_tx: " << *serialized_signed_tx << endl;
			BOOST_REQUIRE(tx_hash != none);
			BOOST_REQUIRE((*tx_hash).size() > 0);
			cout << "bridge__transfers__send_stagenet_coinbase: tx_hash: " << *tx_hash << endl;
			BOOST_REQUIRE(tx_key_string != none);
			BOOST_REQUIRE((*tx_key_string).size() > 0);
			cout << "bridge__transfers__send_stagenet_coinbase: tx_key_string: " << *tx_key_string << endl;
		}
	}
}

//#include "../src/emscr_async_bridge_index.hpp"
//BOOST_AUTO_TEST_CASE(emscr_bridge__send_funds__sweep)
//{
//	using namespace emscr_async_bridge;
//	using namespace beldex_transfer_utils;
//	//
//	boost::property_tree::ptree root;
//	root.put("task_id", "some guid");
//	root.put("nettype_string", string_from_nettype(MAINNET));
//	root.put("to_address_string", "4APbcAKxZ2KPVPMnqa5cPtJK25tr7maE7LrJe67vzumiCtWwjDBvYnHZr18wFexJpih71Mxsjv8b7EpQftpB9NjPPXmZxHN");
//	root.put("from_address_string", "43zxvpcj5Xv9SEkNXbMCG7LPQStHMpFCQCmkmR4u5nzjWwq5Xkv5VmGgYEsHXg4ja2FGRD5wMWbBVMijDTqmmVqm93wHGkg");
//	root.put("sec_viewKey_string", "7bea1907940afdd480eff7c4bcadb478a0fbb626df9e3ed74ae801e18f53e104");
//	root.put("sec_spendKey_string", "4e6d43cd03812b803c6f3206689f5fcc910005fc7e91d50d79b0776dbefcd803");
//	root.put("pub_spendKey_string", "3eb884d3440d71326e27cc07a861b873e72abd339feb654660c36a008a0028b3");
//	root.put("sending_amount", "0");
//	root.put("is_sweeping", "true");
//	root.put("payment_id_string", "d2f602b240fbe624"); // optl
//	root.put("priority", "1");
//	root.put("unlock_time", "0");
//	//
//	emscr_async_bridge::send_funds(args_string_from_root(root));
//}
//

string _send_routine__sweep_getUnspentOuts_dummyReplyJSONStr = "{\"per_kb_fee\":24450000,\"amount\":\"4911514979789\",\"outputs\":[{\"amount\":\"400000000000\",\"public_key\":\"cfdbedf495dc30be82d4934b72af8b1af98b4a35faf984f2c16e4866f45330ae\",\"index\":0,\"global_index\":660333,\"rct\":\"40dd3f5c6c1ff8fe353cb08881c182c29ff7d9ab0055ef36f54514db7e894ef17b1117f21a7ec92dae74f07a6dfdf791eb6d8946615c16ea38ab5a0fb0538d056eb5f5bcd5cccb8b91744845d4f3486eaa9e7d9d2ac51f7364628abf44150100\",\"tx_id\":2455631,\"tx_hash\":\"354d9874b7b13befcf8f079520ad72b78dc62de6081765ce5490345c7623d41a\",\"tx_pub_key\":\"fc7f85bf64c6e4f6aa612dbc8ddb1bb77a9283656e9c2b9e777c9519798622b2\",\"tx_prefix_hash\":\"4448cbd20af2f4f14286707cc35b742e5eaf184037317017794d003457d720e2\",\"spend_key_images\":[\"ae30ee23051dc0bdf10303fbd3b7d8035a958079eb66516b1740f2c9b02c804e\",\"3eb5bdbf119de8b0fea2b52e2c63ebfd2be152713326f7e0acb9c996a9007611\",\"3c8ee840913cb4163f5b705aeb1da0b9b234be67cb61abf21c6648f40964479f\",\"72fb0972751bfbcdd3ba62114d4371a25d54cf0e4c6c8ecb5bc0e3af1fafadab\",\"810aca616598c564ca856330a3677592a5390bdddadf3e82d1563731dd2eef3c\",\"423b9e89ed014f453eed8e914d7d8e77ca9f75805e5251750c35b09120b38755\",\"dde80dee4ed041ffc2d85c020509fbd568e0ce440b9a12a3268ffe5490d027f8\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1293044},{\"amount\":\"364000000000\",\"public_key\":\"583ee3787e11559d0440a2edbdc8ec993f68913a234875d2df401f7726c1dad5\",\"index\":1,\"global_index\":664673,\"rct\":\"98caf1149c4bfdac3603df8649721074aeb36d072a78dedc00c23ad9037ff4b89716ecc91c27637dde21492c6820dbbd4d7be5cc6a1e0ddbb6750a6802f042083f5ebc5807837be21951cf833674a7ea8896661cf6eaa45c0736ffc5fb88fd0a\",\"tx_id\":2457238,\"tx_hash\":\"a727cbcf59cc35f07066b314b53bc6239c4129f60e9ba1c7a8d5591b7a0b3055\",\"tx_pub_key\":\"74b6ba3dd36a85e6e9b5fe4fc093c1e57ec0dc52cbac5e487a2b7a8da091893d\",\"tx_prefix_hash\":\"e6d3a3cf89fa01b093abaeff0085919331ca9cfdadeccfa58ed0d8de528b29ae\",\"spend_key_images\":[\"673ca2516ebb41d612692f3223c367457f685e92c3b6556b28630f9231bf5f54\",\"169baea6bc976ef3bd689e8e810d5d33ca80e2cea6ef28903db324b975a2156b\",\"e848a44a4aefea9d0870bc96d87707e0bf123f311682f252481bbe553e1a91ed\",\"5ddeb3b324094dec2a7ad6091937370c847c870c9abd730ee86062f8a4a93b24\",\"033f1c75e5c5682725f392dc722a14aa28aa6bb05823277065a09e4dd5005881\",\"dbb8e201a3635adf1cddfcd7053eb4d5c3e38afbb41f6cd1311bcf98adda1700\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1293420},{\"amount\":\"238000000000\",\"public_key\":\"fa933b1558dab5303b3e8cb58bf936138bf480bae78c16ca258ab10408d88ccf\",\"index\":1,\"global_index\":666623,\"rct\":\"95f97e430358a5f163b5c26e11a3306bbe9b27275daecc0f013426db9041c00e55efd221fbb8fd0b49c85184b968f2a342c1d09d853272f497da357d78f68d02d4f4b44284ee0468ffa8a05739a2cfd292958e8fdc01d5eaa789d4c9689e3204\",\"tx_id\":2457958,\"tx_hash\":\"cfeef2b05585a781f9310dc0e4d46ab1e9d052cfce11bfd0a58b2b519d20ff49\",\"tx_pub_key\":\"4296d3473870305a732a7bc6a9290f0ec3ced426312ac75501a4211d4ef04c58\",\"tx_prefix_hash\":\"3cbdd08ac6ac67738f871eb254fced02559937c148cd848a616ea5bca9e71e76\",\"spend_key_images\":[\"3bf1610dc8e8dbf16d28400b3bd8c0cc4e673b79152593cc709f88b7b12892d5\",\"ab99d869af5ba68c806e0a8ce2cc1ae2f9b8cf8166162c01523641de5cc1df6b\",\"602b8b4b6c9aa86d9b2ace0b1bfdf9f4b3721650304bf5e79fd0f08ac6b8c363\",\"bda71e2b0b7c501e46e0c4489d1a1f167e1e46c472e78ad7f093d5e52daa386a\",\"a4ccce434fb8d0ec049ab1faf615e965e5024fdd36ff35c856f2cacec34461c0\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1293554},{\"amount\":\"202000000000\",\"public_key\":\"2ee8b8b5a2201ef17bdd4112cdd80242dcaab30826b87206973c8347c8ffa4dc\",\"index\":1,\"global_index\":689429,\"rct\":\"14051b217814eae62febf95e9ee0fa92f5aa7714b1a05ca89ae096494ff81eeee416437476f845c0b2891e9f1d4ef25c283eebd72dbd532463de0b7b74b2b604b29478a9ea4c16d01e67716a8b9d29cb9f49703a15b16f37b73f9e5a2bf2230d\",\"tx_id\":2466863,\"tx_hash\":\"26966c9217160117dc465e959be39264b84819d9875cecc6c8a63c26c7bfc3a3\",\"tx_pub_key\":\"4ff9f870ac27c8f91a8e87d678304801155242c71832dff41a1b64fa8f1fb486\",\"tx_prefix_hash\":\"e4cd3a2ea71bd7c63d8958785c98337bff59dbfda2f8a7f76868e3c9f3d38f84\",\"spend_key_images\":[\"c968adaa4c2323409cecfb6c9b170b86e9c1e5edee8ee60a879a949b892eef4b\",\"f6331c40c29efb0adab369f9d6e91dbc74afc19994efb62ae4d93be7fdd82551\",\"68462abf8bb0b84232694b5fc4bbc2e61af9c5a45c5b5a4d184c5a2dbde2e710\",\"7283f200724f936a52eb3ef6e3627d10b2062fbe921e4e4ecbc8bb8dea45b22e\",\"a46c0d3a2a7fc5d6133ba1d06aceac181c08a4be24af5ceb004895dea129de25\",\"e458af253c58fa717176a9e1bef5acb95314cdf72c71856803e74a471344966c\",\"3abf288f42bcfac84a68db534041ed1fff1d88ad6d86d0b5533e95f07592f6af\",\"df243a771a445712670539d4cfb7690a8dfa9b585e910e658b9dbb85f9ac7f92\",\"854c20ca629d73bcb352524aa774d91046ba668784a336c0d5508571b49345eb\",\"fa7149f2426a712e285cebc60abd113756b50e95ce458566d3c33aab0dbaf5db\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1295703},{\"amount\":\"10000000000\",\"public_key\":\"9f00d23f914640a88ddc81f3682cc91ce3397559de2cc254efe0ec66d229fc02\",\"index\":0,\"global_index\":858164,\"rct\":\"facf8add95bb6dfb2b1a2e47a601b4f071ae2f4cbe86e5e8e6a637be5fcf53fb34c13823e89c70793e0fd688a76f51fc5512a3e2f5468afbf6e8d1034a02ec0b3b5e4fdf48aecd05af069a609f4aa6f97c95fd2163b827f6e328b2b8407dbb07\",\"tx_id\":2530065,\"tx_hash\":\"cc94ab9561f83c8e9148557c41817ac2c669fab6073bc17710338bc62ee9da00\",\"tx_pub_key\":\"f064954f958ebcd52e5745187cdc05ba7d1e97f6fadfda7d19592a07c4485793\",\"tx_prefix_hash\":\"9b1660d1ae7c1686556b9addb36cb50d7ac1d00d9da93c9c5d367751c8f99b2c\",\"spend_key_images\":[\"380623b5bac7c9ddffcad6772020ed9ce33d2992402ed8c98925d6610932010d\",\"a0d862ce256fad836e8b86cf949ab275296648be315c5ebdc765c4a108c5eefb\",\"3e845899d9e4be54ffe1663e4df2e0d4adbba2de3d46f296bd46a69c765cb214\",\"b3066833731be99766c3ac4e06263df516adbaf73603863906dda92bd70c69e5\",\"b0197aedb53d13e2014dab49052ff10483842b22864fd7a388cab9f3b12cf476\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1308574},{\"amount\":\"10000000000\",\"public_key\":\"b8040d94919ba36139c5f0d65cbf9289e4af878eaf0275cfa23518f327cf2c79\",\"index\":0,\"global_index\":881755,\"rct\":\"24fd1b9067e4d142b46f5524f7d358bf5c93a5dceca7c4a2f2b97bfe07100f407180fba6ba1edaa51bc73d4ee11a4c6905f5d9e60ce9ab2c6e4ca2fa6169fd0ebc2604352e19c1b11ef35253c1949d0fb7c49c6a8248bd985527b4d53c2c6708\",\"tx_id\":2538258,\"tx_hash\":\"52bea428c8b1f4a7b610b69d13f1282b11c5454cfaf45b5d9a6f9fa3d68419d2\",\"tx_pub_key\":\"79e4a4ac555b52364ff431cbdc60c18a571cc7d2a3095d3dc46814b7b5e41424\",\"tx_prefix_hash\":\"6159b18174004f0cb1f2081a2e8684b5b893f847b63830d98bcc0f5d3f9dbd30\",\"spend_key_images\":[\"a2c3bcbea52eaa647f943eb77c39786cb10e1c31db95f1d8f5600495bf68912c\",\"c542c24057fe42981e77519438b1ab2151b0ece3b121e560f7469dcfdd84418e\",\"9d6b9825ae47e6e68d8563c8364cd57992739d4d0f0197cc1bd3f077c686a7ba\",\"8838fdf1d1d205f7c43afaddb818d7a9a3f1c3823f051f5d8988cf4df05f476f\",\"5d532af5880278d8bf500d01aaa455e11d66d4dda9df7421870bc0f06e951709\",\"f63d33cb7bcc5b51146b38bf37fc1b0d08264176ad0596143fc4ad0982a2347c\",\"0cbd0b8dd6aeddbedf48124c40011910457eeac05ef67af781672099e8f2f507\",\"20cb1a87c87406815b8bb972ab25b6671dfa455dc7d035f19873254dedcd5d6d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1310696},{\"amount\":\"10000000000\",\"public_key\":\"8a671dd3ed37858f0209c1b4a6e51e2e23b51746a4f1a292329b2283696e9b39\",\"index\":0,\"global_index\":885415,\"rct\":\"8619a32266aa0a43c6f58c21c62a49ef3dd3bb670ce74c79d6839b82ffd60f1840b3db5a7a44082bac00cb519415b395872c89f59e413ccb2aec760867304d0e3a41c66ca5f6af620363abe31abf05350c3b581dda59cf540fbe0f27c3774a01\",\"tx_id\":2539760,\"tx_hash\":\"51abf512229f6c70183d57c0416436011b372e0324292f3ec85d7ec59397e17d\",\"tx_pub_key\":\"d27452265d8e8f846805d88dae30f4dd96a83b93242fe8f8dcef073e9b57e347\",\"tx_prefix_hash\":\"7c597fe4294d0619b236f858bf91238d39d3154c46b334694b0f0daf0550fabd\",\"spend_key_images\":[\"2d222fa9efcb784a989c4643a21ed7b82353f664da6e5ebede075cc75308507b\",\"aafe1e8f8c6a9b805c2d3858f353b22770417ba8dafe8f42d162d6a8bc1ff946\",\"a5fb1f206196a70caef4d166c12d40cf2d5140ac5ff592aa0e4e69f934b9f893\",\"cbcc06e4937f528ebe31c002972820e674ab080ca9686119975277e302a44eb6\",\"46486ea111e342da6a66cc305544fc2eca8243f09ae49014407da4d0675846d7\",\"8d21df42b8dc44bc024b400483bccc383db945bd11c990f7e07b14eab65bbfc4\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1311063},{\"amount\":\"190000000000\",\"public_key\":\"7b46750024acd468a7275b9e53fb921732f3201d4b7f2c4d5dfad236532fc287\",\"index\":1,\"global_index\":908910,\"rct\":\"d85f774ed805bdff1b215867d7f6d53c69e0e3e024a13c50ea7277722d64c68621794c6a7be1a28e976d05e5426725b429879b885b58f02d4203e7777fd37c0bf451948069a93392b630532da5fb9fb43f0780d18955a540871e362e2b790604\",\"tx_id\":2548352,\"tx_hash\":\"005c541070c48667c2a18899a3bdf41b8326657fdf3c1d457a5fd04e8d83a71a\",\"tx_pub_key\":\"a6af4dce2a33e4699e6af4c1bb9a0283b12bfe65583676f5049491d567955f84\",\"tx_prefix_hash\":\"371f694966fa21f793cd820c20b3c34fbf8ddb7329e87d56c80429e22cf63454\",\"spend_key_images\":[\"b13cafab2cdda4205e5bc402a3e6016cef5186847055aee8968868487a96dfba\",\"c7d28a260705b6c550e14c5c123766971234801f6e1505bd02068035b977cfea\",\"f1a3b795daaa403705a984299fe8e5d9b626bbf13bf9cc14aa2b5dabbdcfcda3\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1312932},{\"amount\":\"152000000000\",\"public_key\":\"f102d0c3965a74b235d830b23c0c826e0db90386654d77e54a206b797443ce9a\",\"index\":1,\"global_index\":955439,\"rct\":\"2be5619bfde79a7d7b6212784c2f4c5110e8994aa437608f6879c1d1afb1ae08d5f1cf79b684164d0e0c0a00e55ccc756786fe141d327c71a76b14021bd3610f2cc9db38291802c6281c17f3e0f9fdc6e457146221f04d37b4db21493ee8b90c\",\"tx_id\":2563713,\"tx_hash\":\"a35392ebbc5161fdf50771330b8a2d761076b41f7e980ed710c867c2c08a3968\",\"tx_pub_key\":\"4f45345998d29379592b3366a74e9742e980cced3ad192c8ce38a205d30d0fc2\",\"tx_prefix_hash\":\"446fb6bec6a296c041e56497203b845bfccf056f00b203e702c9fd77dc0e46eb\",\"spend_key_images\":[\"6ac0f3455457ddd1d33878a5be07f0633bf49e0d403a7c2fa3a3e7ecc659ab93\",\"2a8cfac79927e9a0c6662fddac8a40a6a66ed398567ca396d031ec74b19a50c5\",\"53d5c16372a1db04a54c38869a996f92096c2f70ecab1803e3bb0427f252cde8\",\"bb3de5f5eeaae320e8ddeac424db04d86a5a09f7853cfb106ac3b6e009eec880\",\"d1d11fa0d31fceed028eddcbe2f8bb8f2354059cd93247e3c81c90a51e48d12e\",\"0dd83c9cce4f3ba6464d1d0bb2d44c1c4cd2fa20b7f01d1828e50c47922bcabe\",\"b061fef64d70b445fced9cf922840fe66634b93d716ec556807f6428977cda13\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1315998},{\"amount\":\"114000000000\",\"public_key\":\"f2e5849f394da1ebdae610d5e92cf52509cc4c14a901fb1a18a624b8a9d09719\",\"index\":1,\"global_index\":2045312,\"rct\":\"032750d7f37defdb6d48cca411fb879c1ba6773fdabd6eadf18f477003d150b2fcdbe4e51e88ad5ed2f03894c881514549a38849d22005b17986013a65c21a0322bb651a6dad49847e55abdf1fd93a60ba720d2bcf9bf7a1dc2048b85501d104\",\"tx_id\":2887887,\"tx_hash\":\"438992d648949b8a3f899421529082db5f47ad986118ebea7f23f715947eed61\",\"tx_pub_key\":\"bb965edcccec36c802a02950f0ee9ca52d33a7dc3869b34287450e95942fa29c\",\"tx_prefix_hash\":\"a19fa6411dac833c67d2c8c7d8445081c786190e8b432d7bb1dab7182f1d49a9\",\"spend_key_images\":[\"456d6a27caa83b31c28bd03b98f99f07c716a6d4a0429be74cb62f360ae67ade\",\"b66f854af0f3efe4142370e3048b58bea6bcc31fd1fb053230217e1f2eb661fb\",\"7d735cf535a02b867cd4f994ebca98f8f351b122b572fec118d3d803d8f1b773\",\"58317e3111412384bf23ccb3d8399d76d8fa74114e3020ffde77e75a3fda3bb6\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1379639},{\"amount\":\"76000000000\",\"public_key\":\"b7a925f1d0e90089030e68c1c8936fb2211c2ea85c13cff468ad030f313013c9\",\"index\":1,\"global_index\":2832091,\"rct\":\"5042a5330f544f7210160ac37268a68ecc4799837cbe8b487f3a4f82ccd4b6d66cdb683a8794d770a238f59fd876774d1b6fed4e3ee5a4a95946a3bb3d73ad01a052cac36ef6493d3fde4f441f116f6541eb8d993ecfb66818e95ad70120160c\",\"tx_id\":3140308,\"tx_hash\":\"e16e3298ceba01476e565ab7a8b9052dd35b7d863dc8fec535ae81aee3f8f3a5\",\"tx_pub_key\":\"e4f75de415be4f40b595f4514eff9a3629689918a1a8551bd902c22d71d6d146\",\"tx_prefix_hash\":\"1856d924a0f2df7c16fe912a019fb234e064edc5d54dca8185c9321331362656\",\"spend_key_images\":[\"1e2e90e299517d0e1a9bc92281da2e8fa17d01c06c6e982eea87c272668e1591\",\"1fa651980911fa0c6459104fb9684bccc4cdc0d554e2073ef1f1524b10fa4ba4\",\"4d2ded1aaa82c7384befa88954f18835f948269b6cb6966804e38f03593b51fd\",\"930aa770588a5b5fb6aaaaec04d6edc0a47adceb7fb105c1cc43a22673497e41\",\"27f831d10a0d8505bb78f0c60c996ad556a62a6056f3ef133ceef8d43cc54854\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1412210},{\"amount\":\"38000000000\",\"public_key\":\"504f51275213a55d3471a6f37197809ad97751d53a7ed0f0e9189e3dbb4a26b6\",\"index\":1,\"global_index\":2969407,\"rct\":\"ca05def4d2cd5c9fe5fc2b7857eee76866a3375cd58b54d8ec18f3e11fdd695c17e20ffb5e833956e051693e068470a0a5babed2f6e089660e6bedf6f2ed7e0a5d28300efcd87879c64c9e805d475f587e916b877ab55d7edbdeef6724127206\",\"tx_id\":3199725,\"tx_hash\":\"c301e85e205793bcabc5ca73026f2b8ec7612db7becbb1506405b28c52258ae6\",\"tx_pub_key\":\"b03986b855b265a586e595f3b75212d1363c39757d92ce6c79554dbba02e10c6\",\"tx_prefix_hash\":\"77f307826051936892035ef14894dd59e89cd4a4eb700cf68a22df39b474492d\",\"spend_key_images\":[\"6768f8403821b41f93c205fd03c74113c36ec280aecb4b3f53228048450dfa94\",\"5cc3a87503d4c1c8ec6099ae023553b873a40bd99b5edcd3bcd785cba7d927d1\",\"cca663398489512e7169a688c21f1afc08711a76eecd3b7162326b639ee12932\",\"24f26e4ebaaa81f00b491a431e68d2d59a88f0dd83d24c8d90f4fed57ada2bae\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1421493},{\"amount\":\"34478390000\",\"public_key\":\"4d733c87bb898bf2878530b124684ebbaa9efec2c46f1cea83206cbe10a37a88\",\"index\":1,\"global_index\":5168300,\"rct\":\"10f84e81e7a077734c56ed65135ade2d5b735f8ed9de719223550f7397c2cdfa6c370921df73b35e6fb811f5438a40acf0993c253acd7729021ebedee521a902ee664e1bd7fd52e058252851dafa73310de7db4ec2fe381b497b6e0f4347d603\",\"tx_id\":4300016,\"tx_hash\":\"16ef2340703e3f558f8723c2d7a2fad28b5f7c161d0a37e439658b559e6897b8\",\"tx_pub_key\":\"7f0e11580e07b752596a1962f49c5aa33523b426d999a70442c8df60c0fdfc2c\",\"tx_prefix_hash\":\"d9a0c6f8ef5cc381b4158c44c58023b12e0e1116898ace74993837e7210504e9\",\"spend_key_images\":[\"6d801f1f75a57b15d914388bb0f63c5d8c3141c0392b5b82a98b1a60ea60b034\",\"6ad6a3ae8077efd13de32880c565d4fa5eec55634b2b73e3de5ee7d27ce1778b\",\"16600aaded29c1291ee7bf9c4f8703c34d641572eb7c36e41175e4237b868ecc\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1546023},{\"amount\":\"7478390000\",\"public_key\":\"1e54e6a8b616144df6108b137a2767d8afea57ce8ebd3be6514fab178dee73ff\",\"index\":1,\"global_index\":5203798,\"rct\":\"4d347d67aca22dacd4c0a04c10aef95688789d9bf7d0e0f229675ea1c67db427ce5691eb433de54ceb4dae530b9becaec8693a579f93a8ece0b618d9390345042019608b6326ab970246b20ec76236e6e1d8c924c1b387ab5f4b52400478300f\",\"tx_id\":4313732,\"tx_hash\":\"e8872b62ec453b620a36cd0dd3cd7845eaf9063e36cf792e9aae8143ea2faf54\",\"tx_pub_key\":\"da9ee1af535d64ca12fc4f4df0e1548a881f258eab1231b99108d5e4fb226b54\",\"tx_prefix_hash\":\"6696bbbc98579beb7f620f49c65a2e6256ade23adb79250f16d5a1e2c9aded63\",\"spend_key_images\":[\"8664862ddccfccc22ec7ace60b8eada00502f232e7a1a04194dc001a9729f19d\",\"29f7a02397802fe9a7e8c12c76344e13a449177727efc01baab68180c200b14a\",\"82127da987699f709a4524a0225578863c137d6f4837798111c3d7ee2af1a89e\",\"0a83c2558dbb40074a2272d1ff2c262ea2898d07a6bc14ab85a2c25664773bed\",\"5dba6f72c54d854e73a552515ba8371576064b43e7becc9e240792c318dc8a2e\",\"9039fadde09568803eb767511ec4dbc2fd0dc77f8097b72a6972f1af257633af\",\"ade7e6126c0845f5edc73675431e0ec0626079cf51edce1e20a80a1059454697\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1548391},{\"amount\":\"100000000\",\"public_key\":\"14f49a9f325cedc7c18e3baa39346c4c7d789232cc3b502268ee55ea505bfd84\",\"index\":0,\"global_index\":5258882,\"rct\":\"2e8084fcb62ee02fc578e56f8f9f14d2051b5af9e71fc163c757af04cd4325eef0a1e18cf5bad21a027b0a987bb78bb3f73a058eb8c84119335ff1593525df0b192148dddf5be2afb5272747b1eda10e19787a93854eaa740417ad217793860a\",\"tx_id\":4336346,\"tx_hash\":\"ba880ac36bab70a48df64d41cc1161da98b2e60c356220e9a635e46dc11ffa2a\",\"tx_pub_key\":\"c05aa43b69fa85e4da41c8e05f1d993dbb27aaac32fb3c55f5d55e60f9ecd0be\",\"tx_prefix_hash\":\"5277ea4019b67e6239c0855d0899cee53c57ba3e46fcda2b8fc117621b23b47a\",\"spend_key_images\":[\"efcd605b547c5ccfbfa01eb329eb9fb8fc4a20d32b57cfca7392259baea40e39\",\"0a01421957708b4588df83144c200bd6977c8d5b9a46044f20fa8b956a1ce638\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1551296},{\"amount\":\"19800000000\",\"public_key\":\"df7070086ed91afe40855e877b55b9f06a4de01292b614ff96efeaa7dabb619f\",\"index\":0,\"global_index\":5348457,\"rct\":\"343f50bfa2e731845d0bf91bb9d5368cbdc3b9c554eb5fcf3f825fa7697aa836b2daef8a1ae1d3cdf0f20dd44d0275dacf80be167b7521eeb74f6590399d690515c0b4f363ea9187f11b5a22e6b9011b5aca8e79c8390f6c8b7d52a4a4826707\",\"tx_id\":4373446,\"tx_hash\":\"c8b321632e51526e9f497427e1c458f96d64a07429226d9bd53c225373ecf3cc\",\"tx_pub_key\":\"873068949bc7339d11cc20d991e1b25c479b767f28c2a634bd544ce975159a74\",\"tx_prefix_hash\":\"ddc06553661f1417eb086f3d93eb8544ea2a46d7ae703fc7457fdf52cdf1c6fb\",\"spend_key_images\":[\"caf9e5c47d9aece40383f5f9c9127c12e0e3a1347a7fd53a14adfeaeb2449b53\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1555365},{\"amount\":\"100000000000\",\"public_key\":\"7bc63c509ee6f9ef3d028c77281c6d89c23860cadcb7cce58c260d913f93d1f6\",\"index\":0,\"global_index\":5350144,\"rct\":\"8b6c18cf6167b39f07ffa3f834a1885bc80bd2e934072a7a6529fa61494534507ba1b6df0a207ca956d8b331515ce17d0b91cf1b72de58a87d55885471bbf40d11b4e40fd5fdf55ab49a1a906427a90637533d863bbb615db9c23ea5d525b902\",\"tx_id\":4374155,\"tx_hash\":\"81c134d05be0e9497c475b9d11f7d7be99e6f16030314e10c41b22950533b416\",\"tx_pub_key\":\"c7e8317f631a7fe37c7c6d044226e06d5a0dcfdd1bc5c36ccca40d39746a66b3\",\"tx_prefix_hash\":\"0bb10c37af85432cdb60ad0ac72babc5d3786655c91f3154f70f8e070d9de52b\",\"spend_key_images\":[\"1e0549115ba5aaa624e2ed4e9c633bcac285672eb5e8e144bd3957ee6d63cce9\",\"358498c8f46de669ba6b79a02aeab48f7513b29f266e12f36c93e84eb0caa335\",\"eb7aaf206e8e1eb64efea9df6e6cbc1b1222b6b1a643e05ac50454c38ea2be47\",\"13c82c87642c337aead584d4106bff8bd45aa95022d4840d56c45b429a13b315\",\"0df1cb3d286f42879dbd6b9686eae504d15d8576d3b54436d4310f653d74367d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1555430},{\"amount\":\"16330650000\",\"public_key\":\"ccf5b409522fd2ca72e79fa5f91159eea01c2be8bdae7345c0a34a0abfd464b1\",\"index\":1,\"global_index\":5383443,\"rct\":\"94be04f8ff9ea49919c38e27a730ec119c4c9a7f924a5def4b8fc90a080affe6c50fd299cfb2a2add9262aae1b1f0cd212d2b28d5dc8fba2eece1f1a6810140328c02195d853a4697077e51438fbd92f7fed2e1bcd761128b32d078b6c7aa309\",\"tx_id\":4388220,\"tx_hash\":\"a349135312d7c232791686872d30469a6aaac4af163d660265004c1e3fbfdfc7\",\"tx_pub_key\":\"1a47da689e3bceb271ad49285abb071c3fc882116a808c716bb1e84e4e8891cb\",\"tx_prefix_hash\":\"d377e1da4a60ebcea734408c0e5027c434cc656c16eaf8e2faeb5fb7bfa876cc\",\"spend_key_images\":[\"888e748539d3fc707b59acecab4345fc1fc6991887f86d038ffe3ed1546c4468\",\"45c310549f1d113f33193760024806e7748d0b45860da077a31e77ccf1774aed\",\"ebd7de839c7192bf23620fa372c6b92927eccccf6584d8bc9f7bcba7c0c49ab4\",\"b43770e69cbd76326d3f1f13bd6d2b4a299eac4efa57390e011e787da96677d7\",\"92297d76da279403b84b048298ff9c0b13d0e194cc4648b319147b2a9794e426\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1557024},{\"amount\":\"100000000000\",\"public_key\":\"7b3b0a15fdcad2b5d53a839b7bd801b2f3f72865bf2db490b4c5ea69df679b0a\",\"index\":0,\"global_index\":5431776,\"rct\":\"6c9727df934c4cb76fc3d9596892975e5bc917ed98a7d3432351c9e2b29895b2444e3fe7ac90a93acd8432c692fcb59b2a392419c518c1e800ca4e20e4a5040f00e9e6b09c2ac0dd7af961e86f76fbabeeca3f44dd98a4c69ff70ed22f59ec08\",\"tx_id\":4408664,\"tx_hash\":\"ab97a83a57f824f6823b05d0f5102d6e244f91de7a6d7554613328bc1cfa92a7\",\"tx_pub_key\":\"8a95d40a27874393810f9c8891f49f47173361c85d29dccb62ebbc467d355ec0\",\"tx_prefix_hash\":\"fea7e8b07dc9cdcde623ea1fe60fb7e25d5f267fda6bcbb2ad69d06000faf22b\",\"spend_key_images\":[\"96a9dd115ac7cc9f41fc6786cdd3c1f7f240ce801da4cbc9c4cf3adf6b1d7dbf\",\"81d5a929fb5ff3ee137ba9e56c45046c5365ec05bf905e33acd88612b17d167c\",\"a69af31d064dbb8290b6b91c57c8889565da2c60bbe431df187de0a41b284492\",\"889687805ca4b53d4c004cf66ecaa7a927f2fbe27cd1549f8e30c29191f521d5\",\"b98343d9519b0a23b3e12e53e36c86e9a17d01b205382c2f8be75d448d3a1325\",\"884b158365ed4e2dd83e0214679e67e8b997e6e48372087a58255e3cd8fc68fd\",\"944f43baa1b9d7dcaae55165bb884300a215fa192e3d203becda2521a13e1f5a\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1558994},{\"amount\":\"100000000000\",\"public_key\":\"6bc51e519c25909bfb50ef709e1f2207bebdf8b791ef393bc706613224a98b0e\",\"index\":0,\"global_index\":5522695,\"rct\":\"53964930fc141b0e8812b14bc6d6d40714fce3322bb25cd4b3789d755f8a5ad8584de5a0065246e11bcfb4c05071f621ad13f47327a82cbda77f908aedf7f10d3eba2562ddb3bc76698ada8434a6480df26dae7661d7caed06b2c94aaa6edd04\",\"tx_id\":4447024,\"tx_hash\":\"5c7c9abdc37643cfb8e76381eaccbd4e793cb8a6641bc4666e3d69961c880f0a\",\"tx_pub_key\":\"6c99a2d80dbf26be2f4078868e9e4d088b54a354d3b4cc4c0ad755f8d6d6b2b4\",\"tx_prefix_hash\":\"8a611c8cd9205c7e78da506eeea8c9fc6abdda16dda3ff15da72e167a275930f\",\"spend_key_images\":[\"0c38d2ce76a512dd578f364b577eb368998974251ce52630820e7a7890aaf4aa\",\"d07861337e3ae4bb5c4925ab77729c583654833eb40b2bfd4b776665b6f85044\",\"0e222313d38c6e486ae470d565c681424e9b2bee6ae4b86142abae6ce3912849\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1562734},{\"amount\":\"100000000000\",\"public_key\":\"519ff0419a8d0659afcf933dec31c26809bbd2b3052c177eaa9860c831a1af1b\",\"index\":0,\"global_index\":5537631,\"rct\":\"7d3beef925706340848106e2beb9852b5531597005b7d8e4c64d15021818f0ece0f502a533dd2bcdfcbf6211057ee388ebc953974e373ca99ad59679f5633908ec7786afe0c5e509e64d20949d15e0e2b5de2c8e732c3f3dee738db56fdf3f0b\",\"tx_id\":4453311,\"tx_hash\":\"8832cc04312d83484700528b3d2f346ba4e4b9c925fa8fd51b35d865d305f896\",\"tx_pub_key\":\"2f9fbba09c2449ee9e2bff997a7af825cf9efee1cd8bae63312b8869c9274b0f\",\"tx_prefix_hash\":\"9e6fdfcab1aac284e63d2fcb3fa6bd271daea572934783c2d39cdc710abc63a1\",\"spend_key_images\":[\"367fe7b9167d95662e5b0d5415ed467a08d4ff150cf71d47cfcd6b52f25b4343\",\"1c1de9f146c32bdddf29885f237e4d0ec82b851683449c089902df6a68adfe27\",\"438dcc272e7e425deaa2e0dd0e4803a482a38161a3992d49ec37e71a1963a348\",\"d59085fc1ee9bbf8515d423c55c939affdb9e94ffebf0f166f784eec244626ca\",\"4fd0befc144427b6f0f6d4b5633397bdd2b66527bc0e41b5a7ece72dbb537da3\",\"163dfe90f2e90ea964136bc9441e93dd5dff053e3c7340489ae2ed4c4a5dc674\",\"58af2510757787e87692d58559a254333ef3c47fe34119cc79f6bea3fa7a8e51\",\"fc1223fcac351c9c4be159f718c9e139245ea20f018ca0a69777577cce1a735d\",\"70c5861281245a145847ee628f23bff9ec16b5a411f28b4e70ec3409a6197e8c\",\"d33d9831a05cc04b4d81be1cab182a5f0534e2530be60977fdab92220bdfd4de\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563263},{\"amount\":\"87559900000\",\"public_key\":\"827eda2bcd754f0be3494c87b3a5466785e805a8284c4ec97e4561ec185b3dd0\",\"index\":1,\"global_index\":5537789,\"rct\":\"50af66263d0cfd400f60f99da9b7e5a97b4b5d3cd656a012ca39eff2fc005a1729a5bbfed30d385539f9f718f4626c3f584c8a750d993e4f8dce619bb3420b006a2440bae3007132160e6fc381bdfc26d892f65cf3e217fbf3a36c3c5d67c50d\",\"tx_id\":4453385,\"tx_hash\":\"85963e8f8b73fd7328bf8787078d8790eaafe378e3e8f1af1d68ae6185efdb0d\",\"tx_pub_key\":\"53b083744c7ad9d7585eab70601967daab5e5e44dafbe9c9f59f2010226159ae\",\"tx_prefix_hash\":\"8465896fe6f2e11258e97b36e16dbe91c1dbb43a3789b5c7a02df412f0b55f0c\",\"spend_key_images\":[\"c939c9b2d6ac213ec983c6ba5cf72f082b3a44b428d724b5a2ba05a0d4d898f9\",\"fc57f84e9a3f8d50ca60743c7d2e3ba5cfc2ba90dd82e4a1321fb198387d0ed8\",\"c2a90a168585a2c86e20b983f51f4bef4359edf700d910d67ac2d6ad343e6dc8\",\"97193a6133da665739e176e67747753f7d50ed36b3bdb21c5a3b562e20e790b4\",\"e5a1f62a3c9ad2f2a1bfd94993eca20d51466931517629263a89676b70cb334c\",\"8acc65fda821818b10669f04cceab65f87c9ed42b038cc55ab6aea2e0096357f\",\"9fe833677a4ad173f904db29e588583cbb0837d4daecb0d4e07e2193740fced4\",\"952b57f8ac8e4c0774d0698c747f131c7acb6aa2eb004bff9a298ed5e1fee96d\",\"5d4a4aaf72a21d2645ab22d68aee324ab73f94bff2b1a48c387bb18c15a74e59\",\"5d610e216fbe2c7e9be5d906e711814f099779e7d34b8de41d286f8427fff35a\",\"6884de2421afd3cb29077574601adf8c2ba8d4715eb4ee27971a9e94d41f195f\",\"acc1461a4774e7c1a4e65ee907d66a7525fab2d6bed1b2c213c9f0aaedf593b4\",\"7ae95861e2ef7b0704e1c65f6c143da5afb4c90e7d4b8bc259e2bcdabacc2089\",\"3caad9b5d9b6e3f45dcd396778052431e549e0e9e67ef7d4cda4ef14f5cd5b95\",\"5b4941309fc316222624d868189924c92ab1b916dad8567cf828199083ffd737\",\"f9e086dad3d8994cf096b3717a101afb1e2ee9b31aff160d4526fa7db998a7e5\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563270},{\"amount\":\"97160030000\",\"public_key\":\"247f598e7ca4f2f4233f622ff88025f5ba44286b2e4627bddf639e589bdc75fb\",\"index\":1,\"global_index\":5538223,\"rct\":\"413c057b42edcec30da5aa6fd7e9856a04532cd151b04bb1dfe9422a6af8652701780ee0b8d3e729d7b108f1f6c7a23ad7026596641872d02dfaea67e00c3807f9f36ecac939efb766171c34c03a651c40e59f3767a1401860ec3b10210d520b\",\"tx_id\":4453589,\"tx_hash\":\"431b7e2e4068f4ac68a2123cf01154bb72751bd0c1195937db0e4bc1dfa5a42e\",\"tx_pub_key\":\"c0eefff22ad6465550f640e9359dc8fdceb4e8edf6bf63c04bea89decec08592\",\"tx_prefix_hash\":\"cec0c7949ae4f0b40f4c79d6332ea5e2154112711f8646c189c0af3dd3c38ecf\",\"spend_key_images\":[\"c0e7e314b6430e42d90045fa756eb27936e958cd573a839535a81c44ad10d94b\",\"0524758aa4ffded9b0e41769afe981125653ec7d7d44c56140127567bfc86efa\",\"025eb7b8514ee6b8169ab82df306107333e335e2a4ada9e9bfc673edad5bce23\",\"a627d7e0bda9524aba9cefee1e0b7c6833a755aad37b98cd95b685470f131a8d\",\"e6bafe26b74356f3c86e8b19a14bb62d26fdf34a6d7b923764949189de88815d\",\"e19f43631c0e9829d3d8430dc2e14650e2a0d6d4e964a56758d36a8be9c627bb\",\"677433a67901d2f5b5234308617cfc8afd666e3c59243f266139eee14e8671b4\",\"3f4e31c4cc33f5961d1110e998d584b9ba0f9fd0e12ee8425a5d4730e0145e72\",\"cc9a569fc28fb901e9b6904577cec44c53369ca4c1c7cf74d7cd2ea0497ae584\",\"60f789f9c7353947c45a3f2f3af9212b8700ed7328821f97ab38ad93f0092b80\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563288},{\"amount\":\"97372480000\",\"public_key\":\"d47fcececa707d96f92ffc0e0a71ea7879d452a124f5327acfc19883bac3b347\",\"index\":1,\"global_index\":5538667,\"rct\":\"8f00fce772b7afcbe93ee4548831a033d328d84061b1cbf458561f2d3b8a076c2ac5f2962644ce8fe31a4d69b2564b14dd02d932051f6cd1149b9e4f78b0de090b2c2dee8066b5adbbaf7f783535d2e73be03c7bcda7e8ebba28018533a17d08\",\"tx_id\":4453808,\"tx_hash\":\"38b83537e62b8a806fdb530b00880f1bfd68cefc5220581660d875b6464df4f2\",\"tx_pub_key\":\"180a3fafb2eccd74c3afa082d85cf10eacf083f7f40662f430cf5b3cf39c01e4\",\"tx_prefix_hash\":\"ffb0136625ddcf0261eeffaf72c4c13c8873fecd4bec70305e220ef59882d8de\",\"spend_key_images\":[\"a7b23c5022ff346a7f8acfcdc4a7da2dfe52063aad05aecc5c0f9c92316c1fda\",\"52d37258529fb1d62187e6bc64da3c65ba905c2a406fcc5092c9a3bf5c09768e\",\"715cd879c4e0f7ea49c958433e7db2804ba2b7b8041b96534b8018258b467362\",\"d223bf5abbdc0e478db332108c270050fb8726fd3f6fbb337065fe7e02a8d19b\",\"436da83c24eafceca6734f241772c1ee109c5661be1d97487ff097badd6b1c0d\",\"50994900462eac613b26a7e2dd6ae0d6d84e9a0d3861edb2da119e5c72523d55\",\"d3261672132b1eb8c5450b6c7c7519cb45c96aa54708662a7ec423c498556e12\",\"95c3cadf199858e8455b1567865e23e7c598cdb1b402a385c1bf1ac2d95b6a75\",\"381188b2444458ab1818138aab3e43e6b6a434f9fb935f9068a6898839f35a6b\",\"d41c05233d5073ca396c5b637cee23edbba91e67a18e6a8a0b3f036247b78d7d\",\"3af271ce7e12095d6aa711d07326dfea81f44dd40bab728589dea6c5f1b23bba\",\"967013a777a88626ded8840b849c7ae2121ff95b376da7bef21c70e6bbe070e2\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563310},{\"amount\":\"75120970000\",\"public_key\":\"a20c491319c4fc3443bf02467e7500ca74e26f1860a1cf1f01e19887b12d2c15\",\"index\":1,\"global_index\":5543148,\"rct\":\"2015cbfb5606c4a89d6f314b47ac4f0aec62a1e8d9dec37f271bec5817d38e837034e30f4daaaca99f8063cc02b60881df26dc121250cf2338a4b83423d7920227ecddde1dc7b66278f534f12d258984e9d0fa9827a4e512d58c8f4efc1abd09\",\"tx_id\":4455818,\"tx_hash\":\"6551e1aa6ca80b580ef42bc6bad3035f3ddeb3556058b4b30e1926fa4f103d25\",\"tx_pub_key\":\"d195f82fa72e9f4ee41ff32815b53f7badbe7843cd3933dea878dea620591f9d\",\"tx_prefix_hash\":\"73c5742947da4a08d91d5c089a222dcada72e855b77a55226343fe2a053a2ef8\",\"spend_key_images\":[\"f175b3ef4ad5df92cd70c94cfff333273b415a167cdca5eef5ee59440af14cf2\",\"e71c3edb6b3a5e3c6b9f9a45e6dabdff5690c22290179180fcd4244e7603af1a\",\"e8666d5634c4c397220bd3098fe2e821928e3bbe1096759fbed17bb50ae4c0bb\",\"e84bd3697dc1e5de65b96805b40001973d14daaefd2673fdcf1aefb083d07676\",\"84b2da875fe5ffaab6c3a3d2559749f4ce018c6fd71b0c7500c5e42c69cc65d6\",\"85397a19831043d3a98a11dd5066f9a188bae5de1ed33724110f88f2cfcbd6d3\",\"4221f68cbab83324f192c078ad4f71c285f9cbfba11b6ba7f1f2db9335539f0a\",\"0151642afe9f76df1df1c33f47d7c638a30cff61cd6a4c696abc5ad011daf76e\",\"969db606dbf039a93de31d10d0d3d88c405104a3d77a0d8874be319bd2e4c745\",\"b8bf6630ee97c957d688e4d14aed2136d7ffbbacb4b22e897fce4285a50c313f\",\"72a41ab1f0e0e1a9b569a20358d8f55cf45b21840a0599b6cd845347b6cc584f\",\"6c1809dc55982ef17f6a22596233badc870c9c265e326e66e1250490cb29675d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563508},{\"amount\":\"9691720000\",\"public_key\":\"b86207c228d823bc99396ec217f1cdaee479da3f1ff13a3ec5042e0dc3b3c234\",\"index\":1,\"global_index\":5543364,\"rct\":\"88d8fc26b4d7e7e8c026e6c8d326869dd0ec871703e49c741b43badbe22ad3ae93e03c9c9c0ae4e669b49e573f88f3c3b0be0d786f90d02b4431f1a1d488bd0331509861777602c58bc9ce21ad61f55994afaea4c1e5ff714e866162aa7f7604\",\"tx_id\":4455911,\"tx_hash\":\"4b37894519f48fbb4e6f8649af2157c0a5ef796a45128c5ad3a0574af44d4148\",\"tx_pub_key\":\"5e907340e0ebbcce3df3ddc3d69fdc6cf5bf114bf38bcb3c6de1c4825ccec84d\",\"tx_prefix_hash\":\"72125f0d846a9f4b9b4f280a9b148cdbb925ec6707328f5affd6c7929e1cb8d6\",\"spend_key_images\":[\"b0ab441e73ca0188e833664904cd7705e72ad3c39f58355f976adf04795eaff9\",\"24d7079faa48f1d2da838cd24ad7b63ea9f7867d85cddd66c43ee84b124f6aac\",\"e196eeb2f5ef4e77040ee57ead8e76f67075a1e2fef427051c71cd65bb17d9b6\",\"ee30bb4a52deb2c5d5b511259f9a8bd06319332ab2876b952bda2899a4ae3ead\",\"64bc38c550f86286b55e2e76776e74e831d634ce58bf06eef8671fa16b79fc20\",\"0b603b94f80df4d3ffaeb6426e681df6cfe9985b5a386f3f070b367022c1e148\",\"f8676c278b6f47b40593c1b034e94e8f06c9d55300bebdd4e8a5eefeeb555c99\",\"47340d13d0d7f418c24ea0ec763b46711f9badf16ff60261fd2556ddaf9ab8e1\",\"7c87e9a9f232bbc09a4ce16652a141a0d37555ab655ee00577679290f77263cc\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563520},{\"amount\":\"4200000000\",\"public_key\":\"ebdcd4ef1dc5fb6103d8f3a7b455f4d102588b8f684159025214ac263517910a\",\"index\":0,\"global_index\":5543582,\"rct\":\"a036d20302f8c6a0b751e9531a4a5ad8239d9aea3106654352c3f4f50f145796d1352d535fff4f12a035ea6c2f8bda884760c047994eaf45c254ea7e384c8c0f2a1b28b0d778ce457ced09fb41f684ca6ff35b7400c463dfa04ea3ab50dd7809\",\"tx_id\":4456017,\"tx_hash\":\"45c2a12d9e32e4b0487789bd8c3556ddb713c3382248896cfad6c4f7a2619e5e\",\"tx_pub_key\":\"aa15ada55d350c0726242ff075e2a1b15dc3e3a3149b1a045dc4a57fbbc60727\",\"tx_prefix_hash\":\"192b005f8158fc87ca72358b0103495c738fdb952be5580f41e5f992c5ba267f\",\"spend_key_images\":[\"f59adaaed30766275154c0d3e301b49cb41bba40c9eb0aa6758dbe33f386f085\",\"d1284b68cc294170bb9c052a5f6796523cc93b7af900d779299ec54ba5f6bce6\",\"15c5d98a3f0301831a0f17b88150425e68edd789f3e2283f0b22bf88d04c7179\",\"f44d4c363333eec3441c031f4e8b0a3612da74a9b8e9470432edb26170cb81ec\",\"787a2426dee48c321951f9dd20d4ed51424f47eab00583d23b37d3de83ef10c1\",\"55be8718302dd2599e596669f071f680ffa09f7e45f487d5a1586a383f6bd9d7\",\"c0be9eeac0e5b0b77db44cd2918d23fc992be1988412756c8958d4ba6a611bb0\",\"75076666fca8cb7da2e68a51a6e8a3816568f8897037b735014aa71a11a3b704\",\"c3f6318f55e7ac82d9a196295f65a2bbf064b0e88a2e0ec066f695e1cc2a61d3\",\"57516b503ccab39f2f56fb2d26883b5cbcf262f099a108ac5cb122b8e21fbfa7\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563529},{\"amount\":\"68482040000\",\"public_key\":\"c7ff909dbe2da866a324cfdc9888a0642c18eb40fc8edd4d228af5527964423b\",\"index\":1,\"global_index\":5543583,\"rct\":\"bc1448620e91be7eee397d0de62cfc5a02d8d8f693755f465c1204f0e6bbb40569c40b8ec2439d72efd51a4731cf9905c7ce7dafe2ab64d7117aeb023b2c7604765629b5ebf0b08d5f573c6241893ea0904efeaaf16215b8624129d6c74fdf01\",\"tx_id\":4456017,\"tx_hash\":\"45c2a12d9e32e4b0487789bd8c3556ddb713c3382248896cfad6c4f7a2619e5e\",\"tx_pub_key\":\"aa15ada55d350c0726242ff075e2a1b15dc3e3a3149b1a045dc4a57fbbc60727\",\"tx_prefix_hash\":\"192b005f8158fc87ca72358b0103495c738fdb952be5580f41e5f992c5ba267f\",\"spend_key_images\":[\"52f7a6131ee050e9ab2b5786074c59c7c01c304f1f8f8a9c993eb5e5ffbb5e77\",\"d863e722cf6210e5cb52111a1b9df8e65c082e500b1699f30c9b105d907f71da\",\"608a9143e0ef9b38d7e9c13b99c8038954b544ff9a2b9b5d63e0705cee36e16b\",\"bdeb7cc741d08dc562514b4ba56469bfbc938b80a4cdc9ab4ab5536b6ee5e04f\",\"0a01155393b7c6a047728128a9fa8954d4ba42a719dab5c3275a2c5b4d190734\",\"bfba974861e79dcf459c024d5274fab2ebfea6465e61e4583516480f84211166\",\"76c7257f4b90e70bb6f794e5fbf3ac431c0fe12ea04bbbb65b7aa3ad8acdb540\",\"380f66eeb5033bc4ff9d118e1476e234e69c9e5d4c1aa32f96af86c6f50ce3e5\",\"bf1288a95fefef76fc9906d0ff21a2290e77a24e3418e69f6bd86bc13becd0b5\",\"b19eb51039f6dfc968dab460ef4004cbe40863d436277d40aa1f51ad638f016a\",\"cd05de6fc3e4defa3d2756169d0f912c1306416ebbbe99618af410104e9ee235\",\"bcd3cdc9202cedcbfc70f89d8b155f8bd9425074fdd8a15c35710a882ae683d9\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563529},{\"amount\":\"93934070000\",\"public_key\":\"bb50be7d032be5c6375f152e6cf3fa11a5e91fcbdee67935c6850b7d6268c38c\",\"index\":1,\"global_index\":5546148,\"rct\":\"1d2ad548eae2b556861c7b43b41337ff4e6137f8bc678976a70c727c430e2f384107c6927e4dc79806e95732f0d32996479274d1aa1b2a03c056ea94e65559063f2aa6efad8372942a36db33dc38f88dc4d9c7ead635d3b28365081d90e7a104\",\"tx_id\":4457014,\"tx_hash\":\"e3330df01423a9979c7523cd17a11b3c6bb1562f37e12b9bfcea6609f7ab271c\",\"tx_pub_key\":\"94c18bd67a1fc5ebac67b52a9da507a68ad0752425b67a98d8489f1bb38080fc\",\"tx_prefix_hash\":\"19bcfc2ec5c8f9612dc316a61b3b5638bf03b8014141ff5abebc0971577b1d0b\",\"spend_key_images\":[\"9ef106494be9e8f7c2404c8909eb241229fb9c46cbc31d39ce4f63ccf1bea013\",\"49ea048b8a71f496b32ec1dfd8c03e2195a08e48008b4b0ce6c49942bdad0996\",\"23b836cb361a714f7e4917f333acbb208a13324ce2d35e474d37d81cf1267681\",\"d68172c48a5849ee99ba6517d4e99e273d096cdd4079088c136887fb137e6844\",\"a1cc1897228c21191ca35713a6c8e4c3fd1c7cd7c89840d48f9930bdf1a808d6\",\"a6e76dd78d165775c71b6a9c7f29ae9aaaf50713f99ef3df642f688a62bafa04\",\"4b2c9ceeb4277cd84ef4b666fb4f4a1583d44e82b5111a486ca66536291621d7\",\"045ef3e69a230e71a10f76548a001372587a6642ebf67d6c8424a4d889fc2b3d\",\"b264ca31bfec245d20b240ee046d26c1763f99b62642620205fdea8359abd5c8\",\"5d3c447116f18e7bead7e6ba7f721e3122819fb2f18eefc43abac19dbbee64c5\",\"7439a11d3f2fc6f63a787f4301d740c61796cce2f8b6a3b3bfa6bc1958955e01\",\"92658018dd7e4f8969a834e3f87f282be643986c485e2197c05076739a006afa\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563633},{\"amount\":\"94321620000\",\"public_key\":\"0237b873558dca83fc8a7f96dc526582cbb223bb9873c0a17b2de33c232085bf\",\"index\":1,\"global_index\":5546276,\"rct\":\"8eea72e48bdc78ad932c3e2de72fc98e9e326ad3bc077a74f6ddc85c3587305a31b06d6215e2c620f858c32731703bedab902b3a4e18d0ae2f04e38d8a48760d32ed7155ffc17723067b664f76cfdd2e4901bb3bbf3ac1c072aaae4c08b72709\",\"tx_id\":4457051,\"tx_hash\":\"1deadcd9b89801f5fc6b61225635684610cbc1368540cba606e832f99c22a5eb\",\"tx_pub_key\":\"62bbf5a6df44c15186e0b28440c4c721004bed2e3628751aa470f6aed05d2135\",\"tx_prefix_hash\":\"1749c42666689c4bfadebbbe5c7aad55a7dd0599687b549e4978fd6c3b038c8d\",\"spend_key_images\":[\"e4217554c7a1fb3db6b2eaf0567c8ddb990d0e0a9af5d77e7021db484146241e\",\"2581331aa707e005343455b41fd981965a9864a13efe880d453ea39653839207\",\"ac8cd6b543ff9cb4d60e3012e3feaa9ef696ae1c6ffab1b7e4da09b5f16247e0\",\"f31592ceaa1e6d37204038d83008900d67de7cefec3cc4478d1413c51e5ae06f\",\"2ead7d8fa96959692c8b779815174e4b2bfd1e0d65be9f00e3935f471c998167\",\"d063d34e8b28b8488dab1ccd0dac1161642c57e3ba93fe2d4588bbbdca7e5577\",\"fd6472b78391d1474d38fbde23fd6ef349d18ea7190487f1a2351625eda7010f\",\"f0c7c2178a152da4822285b3b5ef2f4cbd7c302b83da52b084cc4da6a5d5715a\",\"d15c70d150849601d7ff008fb71f09167e304b5eb0e8f210594c2759fc969e2c\",\"a14e124629ae6e350771c9ee7edb4675b7687d17f4b19a51fa86b35027bc9b8c\",\"6566bfc64562ab67d4239be4293a92615a0bcf862657b7c18b57345500750167\",\"f7ce8f6e53fe6283d24700a22cbad7ac822d74f52e5069d45537d64191a607df\",\"01f4bada638e01196e231d89cb870b707779bbb968493d17b8fa191dea5c551c\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563637},{\"amount\":\"56043630000\",\"public_key\":\"a33233bbca585b1df69f6c41ff79576f601f573001a504da74b4005e2897c718\",\"index\":1,\"global_index\":5546371,\"rct\":\"d96d20af9850930de3b68c1bd3a0d4271a4821f724bbe17cee4dbf9b6d75645874434574e23e87633ed101b894ba2599411b4549bc82519d37f8f541e79dda080d64f6b75d644120dece711141a086cf46197e08b5cdea2d0daf0589ce41550e\",\"tx_id\":4457100,\"tx_hash\":\"1c41a2f087ef59c629a0440dffa47a5693f920422d24743a65ece48f194ef6a3\",\"tx_pub_key\":\"38cddfe75ca6485672d98a89aec56ed4f9d9c23d6a8742b0dcf6acca5e3ab453\",\"tx_prefix_hash\":\"dd1e43e8f42f56f0c47462ea4e228ac37ceb6a53e5efc49a3dedc3f715379148\",\"spend_key_images\":[\"a15ebc4584cfaac3f0fb228326e4f989cb38ba43eb3d7ad9f22a3e927868e896\",\"410d90d34684d61ef3dfb3a25dea8152773ffd2e49bec31d4e7504a7de45d9b8\",\"1c9ebf665612d9ab5279840194fc854ff522e6a8f5c6eca87eb3f03ba177498f\",\"4ab5918c84decb76d3ae1bf27a62d5c53e786bcba24147cf4774ff81ad0bd32a\",\"f1e55bd462d75720514f83def45901e92d3ea00e78cbc80e2838e5f3987739dd\",\"c8e613c5289043c08a527a486c578a829555f764d5574a2d14d7a750edf7ce98\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563640},{\"amount\":\"49405350000\",\"public_key\":\"4b2ae3eae261c1917bd7a9f788a3ec6114f41f25acb08e4dba074a5af34a45f7\",\"index\":1,\"global_index\":5546799,\"rct\":\"28871c6a86e6f77fe69bd2750a060c8c4b9f48b725574645fd508b8a7fb57f4d5337efb7fd7a7048e88e04d8ec07534fe2309ef2a763b924b0b1d66d09b4ea0163cfcd50c7599df7380addb098aaef5d0c7626b0e0141cd9e10a6822f4cc4602\",\"tx_id\":4457262,\"tx_hash\":\"0784c85fe10b1289ce870cb32136bda13edb2e5ed341d113b6dba11d068e8abf\",\"tx_pub_key\":\"f084d5ec72a888accf63fb1653d02187310520f83bb04f0a9e5d041b5b4b7429\",\"tx_prefix_hash\":\"b22e1f57913bdbd2d84a93f96253d386e2a6ef7dbbc29f2c3f60bb57345dea44\",\"spend_key_images\":[\"7338acc81834a9ffaf3914b451c8a42374e370fd63db3d50e692dcbf13b83eab\",\"2fe0b1176c441f5bc89f38e47057021727354cf0875496c0834b88fbcb97e4b4\",\"fddfd71b3dc43b1cf6f1036506e7cdc00191a2a5174cf5daa6e1585520cfaf6f\",\"b810863f4e7855c019d988ccd0a67c23c1b61a2f3809354a56e267a60cefe20c\",\"35240eb07f0702d12fe0ae4569a26d748e884987c124f976642f09e3f7341f9a\",\"3d6ed7b0b91196c8cb417c342dcd72fcb7518aabf1e3f5b014a02b40729df989\",\"0f82ef9b329373b2a84e9c8a4220ca6ff45baf9c105bf68d546d375d53d457d6\",\"3b27a30420e0cc5cf7e9a75ab914c4f1886eb1c6532564b3971c963fe76fedf6\",\"81b3ef6cd7692ea3216be2a663ff6dc4907fab206b5997f2e1aa13ca78bb557f\",\"9402a7b34be98f9ef0739b09c9edfddee68a33b82165ed73e0e5dc783ee3c6c7\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563655},{\"amount\":\"87683340000\",\"public_key\":\"8235160bed45bffcf6e15a452fdd5f7694cb4bef62f2102b20caafe1fb0a7752\",\"index\":1,\"global_index\":5547009,\"rct\":\"2bf6dfd281e739b9e7af8ce3535ea669c6dd9acb9411fed9494985783aeaa3f0d73184ad5391f450180fac7af419f094a9095d023f948a1c4d999b26b5164f08f30951f89195437106a5d5643778b3733f0fd430dde32cfb5135d2b1afc98107\",\"tx_id\":4457358,\"tx_hash\":\"dd0e40c20616944dd8069d753810110a13ee99f2f82d4713043fb1da3697b206\",\"tx_pub_key\":\"f9cd380f9bb69be4fa653757dfc7c0617f0d40c2c1a07c8e77344b87634d57e7\",\"tx_prefix_hash\":\"2fdf223fcde652a4f55b692969d936400dc1bb85946e7e962a510d845b827f22\",\"spend_key_images\":[\"6bb08a9e1f363ebfff9b3a8e3060cb43232f31e17ee9327f1a1c3a1ee8959c97\",\"238fd721c67ccfd8208fed7a5a6eb3781de7ad66988743601d1041aa49e13785\",\"b20afa21f5e14f9e2d389254d1ca42c06f875247711a8de49e6f4ba2ff3cf5f5\",\"484ff437dcc41b15e3aac20bf9d3c1304344b937af89de64e484e56ddb07c445\",\"7dbf164a975816d062ee8f1f22fa6511422593dedfa5478c99e0b5e375630022\",\"c869ab94a7d5766f4a93465bf1f92ce0cef544db0cb23df6ab6ad0d25d27c0a3\",\"027e3b8f9312bc04e0aad186953a9d71057665dd10f673028b72559d0a138da6\",\"1b61ffe350b74ccdbd17fb23d00bcc72030e161c7e988dacae5733a984fa39fe\",\"5d4d3235a8e3c5174d25853c39da1f7cb75eec375f1a9ab340d0d79a17e80af1\",\"7d908b78b5be69b25d428c6750d39d5e0d7912dff83db0cb9eb3cfff0dfccee1\",\"7ab349b7b1239755af128463585169bcb14a7f12e9636d38b8e1b5e13d94c96a\",\"47168ba5f9a14d6cf7decef473d6a011b6369f1da2b37f7e3953ed5b80c6de33\",\"2b43e5259fbb23a5c253b98e48a2fbc674ab9f9e6200aeff3b4ca101677f7fea\",\"d4136db659ec06511dc00758a7803384d77e682adffbe33c10bb1704edb44e47\",\"7f17f2fbcc73f9a5da9e413be1ce8194940ac53a52d6443a0acf28dc152b2719\",\"ff7c4509d462342fc0071146e00a214dba6f9367079931cdc91672b60ab2a543\",\"2d6d9c7f1f2144e89e8723b0694b4cf11bde67bf1b821ef7bab2e0296c79ad91\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563664},{\"amount\":\"79980950000\",\"public_key\":\"279bf9cd5fdf1d3b4f504d559d247740a05a27841eeeaf61551ffff1d46361f2\",\"index\":1,\"global_index\":5547044,\"rct\":\"471f9c74f03672d1a732f5bc487ead1445b8ac4b91aaf0770379eec8062fc2d1c43f445a780405316c5adf01b91ea6a2fdcdb370d95990849f6d5d1b7ae36606995a6144c07efc2001b4a2b243839e5bc9294fd0508ec9f8087ec234cb57a403\",\"tx_id\":4457378,\"tx_hash\":\"544bb3c725d19b60ad1136923eab3b691b04e5e4c344e4037ee8231fc2f79b0f\",\"tx_pub_key\":\"2f2c3b732fb850768dc6b956f63b2bb8c4b6a722ac2e3e4944bc4f01fc9f330a\",\"tx_prefix_hash\":\"f769e16e2562d1db8052074d3501b9718263d3ba37642de68b3a57cf60a313a1\",\"spend_key_images\":[\"98eb6883e62efdc348fc0542db71988c65be4c6d6f7a9dd2dcc2647fbb265932\",\"b9f0c16239e6251c2ec0e8f9e9c83597008ac9fadc4581d8fe5b2914ca62fecb\",\"f06fc6cfbd5df6c93f2fab15838db79e5c067e7520459ecd86eaf770dda243e2\",\"6d0c0eb3ccd9f863ccd06f9008c6b401c94f53812bcb6cb6787236703d7aa76d\",\"c46b34bd25b6db0e4a08d008ab7fd68700f66aae7cae761d7888c0138bb6d353\",\"0b0ad1b013ddeeac2de40d61bb90af7af125f4fd31627df71744d79ddb692493\",\"21e394e137e9d642880b12b7d5d969e99adc9596fc1989e23cbf2f5bcbf7fde9\",\"df08a63b0f99364cd335c90ea39978717eba651c3b64ee6942f24d5b1eaaeff9\",\"1a6d1fd040de344b0144e8cefb9fa0bf0aeb0b6794824aa4eb1997f7b1ea2f68\",\"a7ba642fc7aa9b0ee49f440f07e4152a59fa86300fce918e8dbf41dfe982a944\",\"910d051d67377f5ee93442ccf5ec2b9a834c3b9f9e12b947888a3aa71ff12c32\",\"4e0b9bbb36ac05039e3871081f965f51a5cedd09db8cbd8f00a6e082ce240cc9\",\"fc445f68ba0e7a5a3668de173d512249c34b7ab703faa13640b143f0c6484d2f\",\"2b1ef2cc3a95e93f46ac0c483f1fc1f72d55a8046a9a683c684995cedd23e9e8\",\"aa2962e7682aa1b4c28b2a4c88b0496bdd5836a67288a94d6dad1699b5b9d5e3\",\"924f7ddffd225f05d12f65831bb8633eeae0799a2647ac9f5900f763802b9c52\",\"ba0fbf5cc3665c1216d69f1445a9fd6c3edf26c4e6c947ca473ba286c4ad8d90\",\"c7840b7511e8ced0d6d5f868158b4b2bf783e0b077cbf8dbf28e44ba894893d2\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563669},{\"amount\":\"36967200000\",\"public_key\":\"7182c1efc8505b4679a2ce678927bac59d04f3d79ddf16607bdd612ccc87f0d3\",\"index\":1,\"global_index\":5547101,\"rct\":\"efbbf9f194f862a125e01451f24f16b76a78f172ab6b6af04923edca6a66964581cf79fbb4604dbd44dca662fec3166d738b12875c6769f3397067983b64240c942cb91d429d66f0e2692d01997df6dd43ec15376df9fc04154c6fff3a26ec0d\",\"tx_id\":4457408,\"tx_hash\":\"d57d0f814fa01609957b9d7a6348924f5daa664d9634e3eac513183fe494a4b3\",\"tx_pub_key\":\"d4055807529530841b283f329a3ba42561c63a6d02a0533c7c86a0525584c095\",\"tx_prefix_hash\":\"424f50aefed9343a7bd426983e407ec73e1412626f4375042170632fcb1d7f4f\",\"spend_key_images\":[\"ce0c6c084a0c9f3ab14e6b856f75eb5a1b890de6a7d09b753e8b8c6b182c7a88\",\"c4c452a00c2a7c0eaebd62e11b64d8e6b92eae1c0a7b4af6a98a0bcf7cb203cb\",\"02f382a1937072e1040c2a8cdeb08f54933e89d56b134f961bb3aa343227430c\",\"0c64fd4b6e072bc2ec9bd97cf523478b89b3dcf44cc5e4030496a79fddbf6432\",\"4f3ad6b61ec3092dea7022de1e1b1863543a2716706c1547da8a135184a3c4bb\",\"a213c388cd18433431248dd499b59502189c9eddb230efc35ecbfa728ba87c68\",\"976b19b34eb852922708dd252c43da713938a8ae3833ff29ab4093bdfe57b588\",\"4ee833a904effaabf95bb6f8a50ac0f580f21f2e187136506aad8dd0e641cce5\",\"57d67e96c57af6d4b492623c27d67214c6796d5bdc26552bbd1b71274e2b8fa8\",\"6d86e4d0006832e3472f6a771e9e41382e315be1c437f2ab6f7e4922c35d859b\",\"fa9f54cb9e9a8cb9dd65a46dbcd58055568193ee21b7859fed27680b37d9f7df\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563673},{\"amount\":\"81045190000\",\"public_key\":\"7342f9afa65ca3deacafc48c3aab66c0a57375ef3d2f23cf6d95ed15470f6a88\",\"index\":1,\"global_index\":5547247,\"rct\":\"02e7f3ea857defd9f8540079f9a5229af5dc3e7db5e4ef6df85948f8ec03dea32b8271dcca33ff31d3440cbda7d43539531610bfe3ee5b173b23a383383b4207b9146766e65bb2a9cfae0618029e3e09bd8f0a1e0f4d6c5d16f02f949fb0e00f\",\"tx_id\":4457480,\"tx_hash\":\"268d6b95fc2b5f2dd3074ca85fae2d7a1145c97a359372757c885d8897adfd12\",\"tx_pub_key\":\"afedbbed731bc4a484b9e9f06264f65d6c6fddb5d391f5794575d299de1d0dbb\",\"tx_prefix_hash\":\"38658ea5c688458cc1702aa9a6a17e8c416c8eb7e2111d3de1a0219d84eb8218\",\"spend_key_images\":[\"5da561487efc9bc4e3a89badcfbd3e3485548097dc312bc4cbe6cf0f380b889d\",\"0b0b971c2e5849aac7065a5e44b1c6a08303d878458942bc54e3c656023dcc3b\",\"e6cd41dab29bd4ce952f667d38a9e1fdefd2cd92a8f43c1c8783e6fcb877f7d1\",\"b2ba79396fc6cbaa967db3363b6404dbf42496f52c03330cdde3c3bc15d08c1e\",\"65bd6ec186cdf93f8915bfd99efd1445f6e31c86b5526872e27798d1123ba3fe\",\"e869e1b38d01a683abb1a0870ac7f868f5f9a5908e82a8e39f471b6e2ce71f2c\",\"76ed5144fc8429c67e523b3f64a84e2346fe3cdc1d3fcfb01a0e0feb69c364e1\",\"5255b5a094b48cc410b114f39b32bfb2fd70ff8186165068e93cffc6882cd37e\",\"379f44d3d36e4ee576136a6a1e7fe0f9bc71e0349740c8d714b057b08cad41de\",\"c1ff7eeef9939c85a9bde2045461a44a4e85d7aa165faea36fe6920ad7dc4080\",\"079b555e483ce56da6f2242b58920d7343b2f65070437373377c4a6283b9f2d6\",\"c22d77b64950b848d08380e6f67a33142a72d4e4d90f1b4af4dcedcdfd885a9a\",\"8253b03b3488158f30f9e00ddadbcc76a1b1e1bf47cf4ba44d10d1591b02b872\",\"07af231c373743ae8599976f5cc9d4431b82547ce8a7c45a6d47d3ba02d7423d\",\"ff7c4509d462342fc0071146e00a214dba6f9367079931cdc91672b60ab2a543\",\"81b3ef6cd7692ea3216be2a663ff6dc4907fab206b5997f2e1aa13ca78bb557f\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563679},{\"amount\":\"73342800000\",\"public_key\":\"7c409d8524eaa6a635995c6f0e34bd62f6d6117726d47344f97ee87df811a3c0\",\"index\":1,\"global_index\":5547367,\"rct\":\"57a2061796f6132ca23801f6f8a9b371dde633f25cc39f368a4a9faaa4570468e1df15df037b9700efc8c02ae728037744c931e2af0d85235d8a009eb3c73007425bee4f04026ca656fb5c6319d938e3cd93ee58396697da51c57f9e0c884b0e\",\"tx_id\":4457523,\"tx_hash\":\"34590e9bc26730528c9bc9856df7f808e19a6648a400c60491f6deac3c190243\",\"tx_pub_key\":\"ada12b3de4086ca9a137a8e93b1d0a7445d0033d0a3accbb22119bd19fcb1bfa\",\"tx_prefix_hash\":\"94e7065bc66a7d1cb6fdf851b583a3fbbd92e5457634c66f3c603b4a42a32e25\",\"spend_key_images\":[\"ab0490adc5558447dd0f4a7ba67296d86a5ac39ffbe2aea7ea19164dd496e3b1\",\"f9855f725551f300eee30df49c979f036da2c93b6b422d49a01e6b4a937bbbd5\",\"6e87ef3a8828c71b5a92599119c3d4d944a0ec0e76539ded0ec417bad5acd85a\",\"050825d15b52c463aa64a3e5ce58491ea7d73a715a5efc017975a7faa51a3bf0\",\"ad69eb6ce593d20810cdd76129a85ab1af176b638cf951feb8dd346a273af935\",\"aa0b85b6bd479a6a359938d58faa0627bd57291a87772a3def32838a1328d3fe\",\"506cb218a8304b31e15f1c5c9d879e1d4783ec5aa1c493273af423fa6f196efc\",\"04c7148c4a79c875f65fbab8c78f2ee090d176fd6bc944a172b4e85c054e45e5\",\"7ffdbecd7b7c6c2c18b0bc9d27982ade71e72c405854f1e484b8e455e63a4634\",\"bc6f868b7947d07e8aa1fff6f3794d7d98379b6e6d559944449c2416e7b342d1\",\"f341ccd7cde29233eab9c567b9989fa03fc168c337fc71bc379cfdd164dd6a9d\",\"2f4c11e6d27be7877eee3fde6694fd81638e1da9f2db51efe335ee7d6fc27295\",\"93fc22f6f01eef45ba6600be8c481983f213b7f77ea0e700ffa05de70a58771d\",\"54ee22a92ed902bc0352c4dcc759300a57bc65ab353d586675cbec6495bde387\",\"8b50e385cc5d924a57beb45b5de13671bc952866d9216a7310ee779596ae3d60\",\"1880285ce1d6cca7540ef5f88b2296c37be8f4c80a1bed6067339b54c1145822\",\"40e96c8f8c50f633b31b9a0153957af0c6e6996fffd4d9e05ed9145f4e215c68\",\"24d1f0a274f62d85750bea824811be9fbf2776fe03e3f4dcf3f00199b1ba9e04\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563683},{\"amount\":\"23014600000\",\"public_key\":\"dc075af6618a9a89dce6820d3c8aae8459f5913de84399e4111f2b8fe05d7957\",\"index\":1,\"global_index\":5547979,\"rct\":\"578dade383408aed71356fd651cd2165e769a643f1615a7627de7a0d084259eb1822b18ff88ecbf897efda7c1def164cee2f42f16f576ee82db41ae59d50f60cf325f41b0bf3b25fb38c221a42411e260d41f3754e7d16c70338343560ba3102\",\"tx_id\":4457800,\"tx_hash\":\"5c2a5cd230a4fa91bcd3020d85302fe5d01f8ea70cbdf32fe169f5ec079d03e0\",\"tx_pub_key\":\"f8f78b3f1a059ce5904ab4dc546cdf98ae8cdb0bfda127506444e556bf808633\",\"tx_prefix_hash\":\"e17d9ab39c7321a2ce3696e8fdfd693530ba8e33ed7bced6ff6c3cd39eb09b71\",\"spend_key_images\":[\"cc31120b25da5482b8f013663c5a87aaa468289679ece506d077838c371ef35a\",\"c06802a320e962e178df85d40d6067e4f631e80d0a511db4a5adc5d7d9941384\",\"2977e272a5755c7a0618e993ef39537a1754467226e8bd4f3647dba04a859173\",\"040209fd6881687ee8173ec6a6d3b5d8d50be4919dd3068c04c7f6e353c1c1f6\",\"0891c44ad963bc425f21219bf3b6a1bacb4aeebbe03d59f07a4dcd69918a9581\",\"b9aa4906bbc5471c63dfec10812526ada41c6bd8b6426d58b13d6b01da95fdea\",\"1aeaa54f6b6bcb5a79030eb149e8d17edbc406800ef5e7ba6c8a2be99aa5a6a2\",\"ab1cabc6febec124bc15d642a4405c85ca378573e318f20158a58ae158375096\",\"b3e359e22490d7c8b231e88b82adc792af9a7ed489fd462798634fef3942f5d0\",\"00db9a306ac771e4c26dbf66a2a0358be6acc8b7cc6dedfeb502a20ab15ef7c0\",\"05a588e8c9ee5e5a7b5830b9e1582b2dce18f643e7e400a8dd7fd34292173a86\",\"f9635cbbd7a8f001670282054558fe81ba9e1d66994cdff83de4726cf3855b0e\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1563697},{\"amount\":\"74509510000\",\"public_key\":\"002a0176b09a1384c5d3caff27ca34152e636a4f8a56791f0baf004664edea83\",\"index\":1,\"global_index\":5560055,\"rct\":\"0574f850eed988d042996ace297930880cd8503ca079a3a8c39b8fccac93c680e916b0958a61462f7e2bfce3073d9f95a76e45da109ad1041671ced88462c600b1cbd42da46695b5ba68e4c90eaaa4bb62d07650622be2464cc6b619d0cb9309\",\"tx_id\":4463130,\"tx_hash\":\"bc7e9084896a2b1255beca80d1a3cb6f52fe792cea6ec86cc9bb78a623f8293f\",\"tx_pub_key\":\"9316d377df27b64c88d448826bb39c9e68b836dc521545464997536252b904a7\",\"tx_prefix_hash\":\"fe2323865fb5e38d105800b292b97a6972744754819c561ccebbe5cf6c366005\",\"spend_key_images\":[\"299deb7744a32b9074d76a4cf4769cea5eb319474079992263c136aee8291ee8\",\"ffc4a702bcaf0285716bafeec701b8e43c0613c55f132b4fb6881e24b7e5f6a7\",\"775127f92f9c79fe1702fd269bc21260cd295b5bfeb52c444f7f398424e4361e\",\"4cea83fd516e0c83cc6bb621c20a3a59fc6018c2f9bf0a48a0722b24604b764f\",\"b6b13a0a4f5b7d72315996cd72535415bb3a287a50e9035a29fe14d2621910d3\",\"a9ec2a439b1b69c009d9e0ad419ec769cfa9829c6a584d23fff0b5ad36d031ea\",\"2cf69bb5fe245aaa2570a0eaf7fb3eb32c5384c8e7104783d40b798675dbddb4\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1564203},{\"amount\":\"16385030000\",\"public_key\":\"e38ea1dd827e0aed9bc27959c7704a95bfefb110404ae1140d934410accb1eff\",\"index\":1,\"global_index\":5595102,\"rct\":\"61dfbd56f9ad75bc69fbdc770072f2c9c33907f81a098dd6f1bb48377f1a2b14dc8885732972800ed252914873cc2e98f19f9a22a81a5770937f53ace310fc08de72e008bbf7e6259995b6b48ff682e67466805cef71b9d5db3eb86214a1df06\",\"tx_id\":4477868,\"tx_hash\":\"a129341da0b00bd3619c6d9f467f25f8463d5642e7ee73112fb61683aca20ea5\",\"tx_pub_key\":\"f3bc5e973d83fcc5f93e19ed1e5a2451b10d4872b8ae2dcd47978154fa7a8c45\",\"tx_prefix_hash\":\"f3329d3ad922945b227b3d1812da80c63a85a4deaa2af4d6d56b6be6f46082f2\",\"spend_key_images\":[\"646627aa81d93c4744ca3b1dbcc6bfa1590c69adc32870bcc1c33e04f551daf9\",\"208a102faf6bc7547ee5f0df428c488895e2efdd2c4bd4148440c8d0eb42fe01\",\"108e1582534c16be2d27c841a62374db94e862b927df058105e9637e3d1f9edb\",\"4c0e3825d1658912bcae5a970fad952fff079d86de4bdf5fd255e03ca6bf5f4f\",\"f085320f7f10d5517042e13343369ed7fab263c72107aee7dd3c86282ec03bb4\",\"b21f5c913482b445de175d461dfd57c37829eac69899c25cb87f5a759c9877c9\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1565546},{\"amount\":\"71080200000\",\"public_key\":\"dcdd4755eb499b6809d4532a84c6cd5591c5537c1a6298076d7718754d1ab4cd\",\"index\":1,\"global_index\":5596429,\"rct\":\"f7b1a8e72d6a7035b0d99870c799fc9f0dbb67d657cc76042e911bcb2d437f90a33e6d2cfdec732d1cde16ff2282105b85e7c1b4ea02e7b26163010624b22409a6ab2ebb6cc2b2b906cbfc28e9c03ec3f5632c966674e6a5bc71af79e4bf240f\",\"tx_id\":4478364,\"tx_hash\":\"c6e37604a383bf0b1a45d638f20a12c72c25704b7bbd14457111fa5c2e39560a\",\"tx_pub_key\":\"6227b7d9ca23b285f1e075739a45d5c38428f764f89701d59d7eaa2e21c0c83b\",\"tx_prefix_hash\":\"98f30987b1fe1d5d309fa9b0373b4080e1fb090cdb7ede2a0a30b86ff136645d\",\"spend_key_images\":[\"c2423aa9cc288796fc977cc7f0c27a789f534021493973d09bd11104ba2bb456\",\"d2e94f9996f97e4568c5e44678c992cc59390bfa197dfcebc5effc5f011f4b9e\",\"b381a13f72c1b497dada70f36999b445405e51832ac491cdd5d85f96856fc0d7\",\"e8fe1f4b42a24adff2535e4b8e554707b2dc42c1f27ea1b67ba0899e0f31893d\",\"a5533512a704350d805d79be07140f907d29690158f1aae7aa1d21dec08ba567\",\"0ce6dbbff6fef9ef8f0ef27d24969751e79c78e588fd729464fd3c47b6fbfc32\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1565598},{\"amount\":\"26520260000\",\"public_key\":\"2dbf01a70fb73b92847d2d870c86682a2f5e64a87d52699dce5aff56e53acd32\",\"index\":0,\"global_index\":5673281,\"rct\":\"a54d9a2a0e9f4f35a72d04357b0aab3193cb35866e3fc45d3468a6ba02c140696c49aceca31b9cbe911c48c2b98e314f39f42416875ca13310b88a1c3db0b60e532c84e3b078a25aaccebc1c13167b31dcc4affbfbf928919ea32bc69108a406\",\"tx_id\":4509839,\"tx_hash\":\"bddf352cbe17fa18b1f0c866395ad25f279c46ebfbfa12d429b9b20abbd89b23\",\"tx_pub_key\":\"c765a484285ba274be89a2b2b6f21e26c15427ab03518db39465d2bcc4385b14\",\"tx_prefix_hash\":\"f9d230364d0dd68d6f237d4cea08602d7f21bbcca320f54cac5d4d5f73f2a361\",\"spend_key_images\":[\"2a20eb8265c0d51ece522e34998cff7d5b96a4dc32208608e7efc73d8c287645\",\"fe765c8f4c2a8e77e7c9b899deee44489d769b9b524679f0fe19d44c1b14ef98\",\"12697d95decbdc99b8f6873e05b7b619bd8d2f213580a111e053e15b8a66cf70\",\"599ddb6f36be25e6116b64afe3f5f525f85c76a147130c09638852201946d62e\",\"ae7715fa6b3160808ebc8a81faa3c8b89b40c092c76241bb3791df92bcec3ab0\",\"5ac8c821f28424f93769a4f1bc97abbf1e186f14c1eb6b5160354d1e7d25d380\",\"39139ac8eafad4d60d6287bbcc3fab3762399ffeb374c38fa9f5519c160d34f1\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1569227},{\"amount\":\"23110580000\",\"public_key\":\"b4cac7facf32d9f4ccc46ece1c8a04719ea8f96f6c9f9c05c5c60b6c39bd6567\",\"index\":1,\"global_index\":5688221,\"rct\":\"9f7f981a6337c9a78dec9f412cff4bafed04aeabf9f2fa5e11916bc739926e920576a4a4ebaaa289b40ff55bd025033e6e3dd14f900c6f07bc240c7b05448c09afcbbc9a7e7e9d0407a3c03422f9250c0aa571c6b1e0943c337b9433bb3af50f\",\"tx_id\":4516261,\"tx_hash\":\"2b83ffe3bbb239a1b34f64d7e701c13304bb940b05039b596ceeecd50e6ab965\",\"tx_pub_key\":\"fef85ea49ac093eeed7cd79bbb953b3eee7ebe0b1e363fa5414061718432abd0\",\"tx_prefix_hash\":\"a23535506c0600514a8cad5d0326039af041aba2397872c00a078bc108c8df06\",\"spend_key_images\":[\"cfc9e18928195f37f6a837e4e0a0e66707ec083048f2fae0bbd04c451049ffaa\",\"0bcac3026cf0dc001e40a35b869b79cfa1118fd53f2980ba7e1b40bfc0d78ca1\",\"5fc2965693ae5dbf5e6f9cbefe80368f3fb8eb275b57cae4c9f3c71ddf64d90a\",\"5c95f42d7b4263c34aa30629f123510d8cb774fb42db3141c630cdb8a32544cc\",\"cc5967875e33bade5defe1e5be3e8d0db73becb2bdd4c1f3d394d66ebc409e4e\",\"6207a4ed10f47b37fbc7d6dbb5f503ea45295d46c5325e6dc630e46be670d109\",\"6e9410494c7337c7d522ac4e9070d17e63a015ca7ecfffcb7db6c8612a03a56a\",\"523eba6fc77849e1c942ca272f6344718a62074d510261050d062550e40d52df\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1569852},{\"amount\":\"10701160000\",\"public_key\":\"2e7b9fb7d4a9c4bfa01a4bc43f8bdc7cd3c87a1d150f288928ad42fa154f6028\",\"index\":1,\"global_index\":5689777,\"rct\":\"ddd88004b4505bff15ade6a090d5cee90fcab47dade612de2d472dddc9b7abcd1d53f62ee0b22c89910b01f9be746657e3259a5c460b216491185f2cb424a400574be78b0d4c595317548a65a3f7e0a635aa8d7cf5789fc3e5e6191070bc9c06\",\"tx_id\":4516963,\"tx_hash\":\"85c339a313e45325354bcb06cb411f1aca4c1f893602bfc4d757bc313d098073\",\"tx_pub_key\":\"0fb65fc3a72ef2301ceb99fd6c53d7d8d859378aeee1538e7681de75e289d875\",\"tx_prefix_hash\":\"711f39bcdd888c3cd131fae9a68a5bfd38aff3a7d68c48882733134de580c66d\",\"spend_key_images\":[\"9e146649df25712e45fcf7050cfe6e19c5c334304c906ec9a15e4bdcaae68dcc\",\"b58f8604880a46f70f545007f16a0a449a9c805e83a8971bbfb3ea120a773614\",\"9416c3749ed43a5d16cda7688138f6c68786d70c28a9740d4d0b02ec30fd7b79\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1569914},{\"amount\":\"4876130000\",\"public_key\":\"c3f97eac69fc4705c98dc529f771fa10d4f96aa990e3a439140b84d7255c4b96\",\"index\":0,\"global_index\":5691659,\"rct\":\"c234a8b2322a3f6a21eff1c92c8525691578af2a1565a3d442d1e9d5cbe09097a49045301ceb7b8f470c1c2147109f001eef8613df4357470d97cc93c9f70f0f922ed27fd529c371b4bd3b2b0cb86f583eff9226db4d31bb0541db5d7fdc5d00\",\"tx_id\":4517778,\"tx_hash\":\"b79a2dbf553698ca7994eb817b69755f0a113406834bb42ba5739d2b7a66537c\",\"tx_pub_key\":\"a498be7626112de3c3d2f2c60b43b9f8ccee4fd24146710217f4932c2db55d23\",\"tx_prefix_hash\":\"ca21368459ed2436db6ba7ce2da9301176257b821129dd57c569075951338f5b\",\"spend_key_images\":[\"ffd06583dbf2f6179c9b1e79020e164ae9e59e6fa9d4feff05a9e7539f02c31d\",\"e6344962846a2497d04d0046c5f59b4b9ed8952abeea9a64a490e772bb4b4ee5\",\"1a76a80ab613fc257e9483ae8f6050f427ce1a2f75d5efc704a6bab702628b35\",\"6ff75141932257c086940b785ae067b436a64f3db5339bb785c4cc559905e023\",\"53653ddd1e4070fd0e239931d733252d9c266740527cd442935ba346369b5a11\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1570000},{\"amount\":\"108939270000\",\"public_key\":\"b93e677a78988acc284d5f7cd75aae7cf2a40b6e4c7cbdb5cddc0124bd9cffa6\",\"index\":0,\"global_index\":5985342,\"rct\":\"ae537509f7c0a2d6e6d5427366abbf6e83f12730eeddcbf3770cdb98c46089417efa859da9c295a353eb7694ba54487718e3e6055aaef13e34903bdde437ae0d81d7d9ba2a81be2c7edda77a83c0eab0079bbce3016f5c3e6b92fe36d8e21c07\",\"tx_id\":4637225,\"tx_hash\":\"9ec89ae9758d59b71807e155bf9c8a41be9059629d1822b6e571fbd8bc40c3c7\",\"tx_pub_key\":\"61961045688eb0609403e5da393432bf4c60970e67c365b1f7db43002c379b9e\",\"tx_prefix_hash\":\"80389610393bb48cfc520d898ff08cf88aeeaa2946f3c7d3a512413657861ce4\",\"spend_key_images\":[\"438583a045681b88d383dbda64117019d0298be8262fd9333cb01c1f5210e788\",\"011613d0af995e845b695b9d0c363b03295fdb9b4e891a1944c589ecaa73f86d\",\"9d134b6c20ac7578e44a82002a9fa27787df7f1939e0c4320d128b8fa3c463e9\",\"517dfc02c8fcde7d9c3309a6c4e6de20f5a1320b051e015eae027826db63922e\",\"a2b67cc48cff05079adc8abc8537e744656973b81b5b856d643e0cace2102273\",\"766ebd7120217a1db09bfd2bbd92ee51890dfdc0649556c88a27269c434f40b0\",\"b30d3dff87584d6bf6df8fb5f8355e231b058ac6859c27a43ac1f45b0ab6d867\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1585095},{\"amount\":\"105614480000\",\"public_key\":\"d667b252987a54186d53444faa85f088d8156b2aa5373be14ac5eaa615bfc2c8\",\"index\":1,\"global_index\":6053800,\"rct\":\"b85d9d2ee7d7857b2f84202ad940bf26d9c1fa01aa7ca63d9e0a2a140e08d3c50d1b3c461300a70447703c6240a9ded099ab60fee2081b2a66c023a76151f605ada15e90da99212b00ee2316ecbaa01203fe0b8b6c0881fceffa4583444fc403\",\"tx_id\":4665124,\"tx_hash\":\"971ee2756367f7b64576ca1c9091226183d68fc5b1d4d02b951b4ebfd64cdca4\",\"tx_pub_key\":\"3542c5891fd1f93cbca0282bd56920af3f85ef027130230a03c17268e519de81\",\"tx_prefix_hash\":\"2b5644490420bb718ec9618062a4c07dc646f2f55dbc203f701909771bb1e6af\",\"spend_key_images\":[\"6465fe4e2dc72bee013b78f9a7f72ccc3e79a3a9e498f641ea580110c8c234d4\",\"bc39be245abb74bfea959e62a0f91d65efd42e8233adfd6dec0ab3cac0ade929\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1588657},{\"amount\":\"1000000000\",\"public_key\":\"7b38f208c21380704623f26ad22e4b34bd0d254b55c7b61761be64d3d73b16f6\",\"index\":0,\"global_index\":6080781,\"rct\":\"d31fe6c05af416d8a575b86ec9d77ad141d6868c59d3333f8678f2b8ec76573bd52cb43ceec4da4b4117cdc571b91cdb0d464926b6e333ac2032c6fc7c9f1e05da08452c4ec68a8e11fbe40e424f6cb8c5389ca574b7f4a69c3aad521f955f08\",\"tx_id\":4681057,\"tx_hash\":\"4c528aa2a44be301f75521303a6fe5ea043faa28392fe9185b8fa9dca4a2a264\",\"tx_pub_key\":\"51416b813c4d1e0ff56c66ad937e80eb029244edbd45917073c823ccb24d2225\",\"tx_prefix_hash\":\"ec89988b06771e1964b38d6aa6ed27a0a3015b005a7f476f3d1007085ef795c4\",\"spend_key_images\":[\"ed752dccd65dc81ccf8c99f95ca1347ebf25d2757e6bd45e743ce9d7d093061c\",\"4a742c59b7a1b207ee5df772e687fda90146536bb0fb5cda60e746a97c07b360\",\"f48ada5e549330e66b8f740183f5585a92641788d9b73e01dd066b07d0972793\",\"4c1b9f42913621ae27b8b4d7da7ef7c4a16c5b538171431aa79f6e5d826140fe\",\"4830dffbf319ce124523d27a9afe8f2769cbfb3db66b680d5008829e38837422\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1590103},{\"amount\":\"93296320000\",\"public_key\":\"0838cba3ae737862c968a5d2bf97a19da13b97300da77c0f77cf01acb7f2b795\",\"index\":1,\"global_index\":6081835,\"rct\":\"877000fd756fecfd5d37e049ee4a7f45f4e9a11959f44791d186a724baff6cf860c365c19f91c1ca7a3daaaac7e9e9d0efe2b21650a643fdca728baffbfeb708a16d44fa1c189a9e0f3b9c7eebd4190145606cae9787d4d8f93e27c93aeac109\",\"tx_id\":4681518,\"tx_hash\":\"d89e0209970460765d730bbebc7e676874aed0ef365fcf4ce0015f875fcaeb32\",\"tx_pub_key\":\"02778bc7ade961954413722e06851f68f3f0dfdbbb103c9576447305d6df0ffc\",\"tx_prefix_hash\":\"2831bbd908f98a5b049d8710cf541e911145e22a87ee833d0019410cda581dc7\",\"spend_key_images\":[\"f0ead47bb4bd3c9d44644c65f0d386a6149c63d09ab4833a16204b1982f5d628\",\"3da9c9c21453f452a27f45f605c7c4764bcab359e5efc03be3712026f88e15a1\",\"ecebb4b03e21cb29e1e9640051d5b1f01180820159743d34cfa6673c487f8eca\",\"12a008a3203afb2d858f7f68f130591444f8ac79b777561f055facac9824e7aa\",\"921f343ec7351ffa8ba7b1fcc58e8d6367d89e0f04085ec1aa3262ea3da7f19e\",\"75f7141e298261f25f23a2bae1e1ffe5dfc90accb7e75408c9e65c9270c0ab37\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1590158},{\"amount\":\"125000000000\",\"public_key\":\"596fa47b6b3905269503435099a05e3ede54564026c93cbe5285e2df074c7118\",\"index\":0,\"global_index\":6451664,\"rct\":\"920ee8d99299f304d17fdb104720d1f62be0b03383c7bb466ff39c6a264d80d616ce1eccd6c4de1cc0fba87e463f2e0c373146c475e8a1517f36e7a37351d50034688cc8cb528c14188cae45d89b313d444e583c9d68a32cb80938a5e2aa200b\",\"tx_id\":4835461,\"tx_hash\":\"0c3bf04ec0b89b5f48ba866f33617abb563521a4d3d9614604a63d9c97b20787\",\"tx_pub_key\":\"0a86e588dc67ca11993737e003a9e60c57174a663a47495e3b1d764f486fc88f\",\"tx_prefix_hash\":\"29612728b44d921efce13cfc49042d6a0f5b921b99968b35c4474551c233e609\",\"spend_key_images\":[\"40d71ed2e4fed3a117d64e1288689cdd22fa7fcb325459a34d6237a26085ce85\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1612967},{\"amount\":\"112832250000\",\"public_key\":\"bc1f35e9d24c264b6c22270604e2779bcb0eaa34492b18972a14b5f9c38aad58\",\"index\":0,\"global_index\":6671209,\"rct\":\"35d14853f4fa61f0a0a6106f7f7aca13997debe25b7e137263b6859e74a0da2ccd5e787e3dcbf40ee5a9b444ec9de85bfbcf52d43ca358996171765f86748c00fa2510258f8f56575e46573f70748e7c3daec47302f4aa784a731e82311f1201\",\"tx_id\":4928046,\"tx_hash\":\"6de303c846bbdc07d67b665ebed01b140770a6bc89adef4c29158abf2f9583f9\",\"tx_pub_key\":\"3ea5ee7a01836af04a0a5ed8ff1ff70869a07b3342179f40904e87645b2dafd0\",\"tx_prefix_hash\":\"bbcc974f29502d3d57ed36c55f2ea1f5be5a36516ce57ad2dea1d649f972d242\",\"spend_key_images\":[\"30a58d44a9c052d8b4f0dbb43b10aaf8f450056714a3814c616eb21c2bc0dbe5\",\"f3b1a1dc465dde3c0235d245a6cd03203972785c4c0c0c7664689ad6075db5b0\",\"4d83a310db65b61eb6e6bce7b9b92270686c98c57cb52785784eb093308f8826\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1626846},{\"amount\":\"10000000000\",\"public_key\":\"4eb8101617ddd0de80d93c599c932f990bd32c3dd34b5dd886ac9a1b1d4f7103\",\"index\":1,\"global_index\":6671210,\"rct\":\"2039157f32f47dad6cf010e2405b080ef42dc2ce25d651d3761abf45cdb8114c4a6efba1b9ba52cff5b1de259a7d4ec4da351aab122c735157beb2807b600f0f1a3a2a3f8353b410b35dd34da123366c47368ded13f9a3387215ccc1f84b900c\",\"tx_id\":4928046,\"tx_hash\":\"6de303c846bbdc07d67b665ebed01b140770a6bc89adef4c29158abf2f9583f9\",\"tx_pub_key\":\"3ea5ee7a01836af04a0a5ed8ff1ff70869a07b3342179f40904e87645b2dafd0\",\"tx_prefix_hash\":\"bbcc974f29502d3d57ed36c55f2ea1f5be5a36516ce57ad2dea1d649f972d242\",\"spend_key_images\":[\"c32666a7fcf65f0e28b5abc1a091f529942f90ce5a3ca30ba476a3a4726e7405\",\"b53a1de7fb22042885c2329191959fc6a14a3f8ded1beea7336a0ffefa3e8a32\",\"b42ff01ea39ffd5a4403e678b4c3701054191646129bb275d49ec471b59ab6dd\",\"2fbc12d357b90b1dfe232c65b5e2abb0cac8c12ee8f584e6cdb3e87419372e9f\",\"508989d6f765054421e80a836263989cc72f84857825555005c3f64540838c57\",\"a536b3d2204470ecf70156af5ed7f194c44b1fb17d01e312d7ba499c9fd50f3b\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1626846},{\"amount\":\"100000000\",\"public_key\":\"482753667ebfb79947fa4e6f60ba801e14c173cc7cc69eab247aa0b7b855164e\",\"index\":0,\"global_index\":6689728,\"rct\":\"03f1f3f461a529873d6a55e41e620675c56a91768bda13dc58c24930160eb9e99d6da01bfa73dc1c21642bd832e002dc53cc1cb85c19a499f6c98d7bd28a4304558c29ad81465ca932e120a47ce1671bef0a186123de0a9bc4559f4c28e07b0c\",\"tx_id\":4935678,\"tx_hash\":\"41782cf2d4ae5e5914ab79ea0bea75fde9cbbe694a65f889eb6af833c24389b2\",\"tx_pub_key\":\"f1f8985047b24989e900ca988d6f5657c404768ef3d3e198c343543a7dda4917\",\"tx_prefix_hash\":\"585f7ce7ad4a8b75e5d76f97460a7160b5a8748d9ec23e603f9bab304a17386d\",\"spend_key_images\":[\"6b15aed045da27cce5fff01a11cff589ff455fcc43ef34193c36c0da56827f3e\",\"48c18ca26f4f88cab5f4bb190c35da92fa5d516263ee7032b5ab03ce4d6a3eff\",\"355fead5a8959ae86430f669a0b47e25c4eb5cf25e2a0a629eeeb42e61ab8355\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628066},{\"amount\":\"110575810000\",\"public_key\":\"95ddd7a56e3759662f3f0ef3e0e8acfb8de0458c9ccf2d09d5fb4fe9d79a7acf\",\"index\":1,\"global_index\":6689729,\"rct\":\"10d64bdc890badb17e125ef4ca5bb49cd7e04415b9453f280fab265021f42417a36e2c2cd4d28a7c90b5614f55411593800c8a944afbe2b3c3dfeababee2550f88ccc4eabbea5948766cd106b46227ad388e28a631ff7566e71a77f56376f702\",\"tx_id\":4935678,\"tx_hash\":\"41782cf2d4ae5e5914ab79ea0bea75fde9cbbe694a65f889eb6af833c24389b2\",\"tx_pub_key\":\"f1f8985047b24989e900ca988d6f5657c404768ef3d3e198c343543a7dda4917\",\"tx_prefix_hash\":\"585f7ce7ad4a8b75e5d76f97460a7160b5a8748d9ec23e603f9bab304a17386d\",\"spend_key_images\":[\"e80233aea0769e9f8bc7ee7590effa495e37169b4c9d31d000dbdc29e06ad59c\",\"ee9beb027cc75cf63926daa01419e4b4e7459bade849316b4b7f7d4858aa005d\",\"b365386650dd8480348eff35981614b0cfe8ff7014660b9c834b2a75c479b417\",\"4bda92fac52bc7954e14b1c214f4e4b6c7c6848ce581afa974fa1d3ba8f54bd7\",\"43a3842056b87767d01796bfd9ed50b1bc3aa6c64191eb193913d79f3051fabc\",\"655e0c3de33c30709ab33e058a269e38d34863a8bfda951cd8d931308f4e4557\",\"bf4a325a9a0731e8aed46b2f3eb35e6774472bc81c47898e4615b01ac716c655\",\"1b6e542c221b2cadbe3ca4a6efa96c84872dac11d3b9e29be842eec1d94fd6bb\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628066},{\"amount\":\"974000000\",\"public_key\":\"90146973a01778717b59978b2a597aec0f76506f72d33945d88e8c2c959cae7e\",\"index\":0,\"global_index\":6689950,\"rct\":\"fbf85baed0cd82d985665a69d08d0dbfa70600184689b60f5cbc2ec1769c3d78c1c189692bf1cdd75bfd38f9ba9b9a9cd0958d4e2c0cf6e2c906e60d19e6f4014a2b1da321bba9f2caa3707c36fd3e03cd901ce2efde29bf2f69a1b24461230a\",\"tx_id\":4935737,\"tx_hash\":\"6816103910242859912554d9320e1aec8b89bebc5c27cab6bcbda7a14cd0d937\",\"tx_pub_key\":\"785c82da5ecdbfd02967b7538a3b2d3e3074a34f3b864dc360d2e2ff99e08e2d\",\"tx_prefix_hash\":\"59f6b0ab0d6aff31a0597ce4c1ab09b4b4660066da94be79d5efbc2bf3280e87\",\"spend_key_images\":[\"29855040ba4812f7029a5f20027e4d02dbe1aae14a1f0f8bdd94c9979623c55f\",\"c4eb880538bcf3bfa5ef5dd13d395d5b07a604291c413d588c5bb2bce4b3e86d\",\"014cb772896ea304d3861ab32e51eb8e4d314d94d0ad3ff703b26906fb65d52c\",\"7706057557717edef5e8c7bd0a12297b902597c188b33ed7a6a69516724570d1\",\"e902a0fab7974dcd512e34648188ecfb9107ced21d3b4f47319004d343138d16\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628073},{\"amount\":\"100000000000\",\"public_key\":\"de0cbfa80ca36685a7ce10e007d1c5c22de55ce8f33071d3f6a0b1e7d49fb27e\",\"index\":1,\"global_index\":6689951,\"rct\":\"be3e1a8f64e1942d4d0c65b4c50f281845ca9eae570c58bfdd98e501ed626e220fb3b1efbe2c4e320887e2b4a27183b7c57ee8b667a2b815b1716ef60c4a5f0cf87fcff87e8e1c957d083eb0e28a757b10b570bb534283795d01d22082a21409\",\"tx_id\":4935737,\"tx_hash\":\"6816103910242859912554d9320e1aec8b89bebc5c27cab6bcbda7a14cd0d937\",\"tx_pub_key\":\"785c82da5ecdbfd02967b7538a3b2d3e3074a34f3b864dc360d2e2ff99e08e2d\",\"tx_prefix_hash\":\"59f6b0ab0d6aff31a0597ce4c1ab09b4b4660066da94be79d5efbc2bf3280e87\",\"spend_key_images\":[\"9b5bb0fb7ae8ff39fd30aec7c56ebc7b81c4675340c3f803a92031020ad2205a\",\"eb7497ab8fa4af7864c04495f919a789c596ee289b772584d36c6f3113aa9039\",\"5439e04c01ebcb1ae9353d28be0bfd24fbf8a5deb6b4828e941ee6578f30bf29\",\"8afca1b1b4f35917fbc0c19f6f4e092c56d11d8bff0cbf81e27d7ec005f3b519\",\"c8bb4de7c95ceb569b9efeed5841d027e0e062a80dce7be87f7980b242967166\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628073},{\"amount\":\"1000000000\",\"public_key\":\"aab6ad62a7486d79a0ab2af89b71c8b8fbf7eb94ed9968acec83f27b5c7ff8cb\",\"index\":0,\"global_index\":6690021,\"rct\":\"c5798a17e3111188e3481737cfb9feb078a85b0651ef3800daa009cd45103ae33b403685c4e3598bb1bddd2349a194045cfe258aeb9c6c8349cafbb48fe3050f9d0319c12551a815b670425d81a46d05f9780edf61d1c386344c32fa3cfe290c\",\"tx_id\":4935775,\"tx_hash\":\"331fe93e7a6251468aa578bd4abe857493cfaa51e7ddc7318a9b5991d1d316d6\",\"tx_pub_key\":\"1b856a3e999277a761c99ebf6f9b06e9bdc009c0a251436d1000c7830d0d8ef6\",\"tx_prefix_hash\":\"ff0bfe5f7b23bebee13be8145615748b643e1b8cbdbcb63bfe3435abe13cb759\",\"spend_key_images\":[\"f36ce348741e53ea82f8fe0f2c3bbe02e84643c0e95553252395070a76303cd6\",\"ac71494d91c19e6abdd1fbf8a356df96b846ad38f35d9a134dad113b3804c5e1\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628078},{\"amount\":\"107419370000\",\"public_key\":\"9e4f0084c736ec7b9dcc23cadec88b3c110efaa2c2ee767afa9bf27338b3a48a\",\"index\":1,\"global_index\":6690022,\"rct\":\"57863026d99dd84f26ace27081843f0216e26b3bf89afa85f57c0622fe61c9b6839857bf644568d3d98412d92f990d81a5cb81d1e2015cae845dfc69e0f450001906cb70a00fd6321ec4abaf86408008b7f9a0a7ccfb2fe4f59112c6257c1b00\",\"tx_id\":4935775,\"tx_hash\":\"331fe93e7a6251468aa578bd4abe857493cfaa51e7ddc7318a9b5991d1d316d6\",\"tx_pub_key\":\"1b856a3e999277a761c99ebf6f9b06e9bdc009c0a251436d1000c7830d0d8ef6\",\"tx_prefix_hash\":\"ff0bfe5f7b23bebee13be8145615748b643e1b8cbdbcb63bfe3435abe13cb759\",\"spend_key_images\":[\"6e8b3d19fff3378fc0a03f98455ce4fdd8ce886e39467d31cf00e996f754960d\",\"bdcf750326b4e42f6ef5a3eca608729a7324a174667349f5a010687cb06c8005\",\"b7f1879fe036bf08570e892db309189aae82b40284ed3e75cf489cf1fcf79382\",\"d47567fb522b7f162d66629170760e195df5835cd8f6f9952905e437b8cbaf9f\",\"385007c37a3b827a645cea98a4c82c8aa58665633f7953727557e5bf864420dc\",\"e7aa3ccd23f54c7cd5465b29e1d4ab68e2edd900f554af56cc76963d0ac11699\",\"32729f040e484e7d56c1685805d474b9e2371e87b906e6fa50ddbe9b0667d9c2\",\"391a64e49b72f78e57ac8e860d4435099541e4474e7f035569e178667aebf423\",\"9c49078b2fa579e264d275f0b2b32e61f3ea39e2f6840474d45cd67a57cac3ce\",\"d1344d525d0b3c7278c101482bfc257217965c7b0b171e5d296ed52f42693266\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628078},{\"amount\":\"10000000000\",\"public_key\":\"2e6b9ec7b16b682e8719ba9571195a51a9f85a02d42edd7c957e2591692522e7\",\"index\":0,\"global_index\":6690228,\"rct\":\"dc18c45859d4451a71b7faf89a7d708e7536a876a3b67a4e054bc8da08f477fcc3488e456e7a39c95735b9d1b6a3024c9de67106aeca41f81a091abad673aa04d4300a2dc554a76c1a5e09e3d98c7310d9e7e8242b838c3199ff71da78afcf01\",\"tx_id\":4935858,\"tx_hash\":\"eabd7d09be07fbc449d373bc5e839c5c2ee74602f7b1edd8f28607645784478d\",\"tx_pub_key\":\"d54bddee539a2cb41e88fb5daddedf98353a97eb6b44dcd0fc96c76722a684e8\",\"tx_prefix_hash\":\"10c3f97fd4e02739b7c7858a524e2b1d9a7fbb76a86ef9ee237a17bdfb071b25\",\"spend_key_images\":[\"1e9b3f5c51402807b61246262ae0e818025661dcf1c93be7a58f7a460334aa66\",\"2109b72516d363cdccf7b5c308faf3dfecdce8801e2e01d0b53e9be8506bde89\",\"3fb7ae75f37480a6374ed9eb5982c125eff8cdc844afa06bcc272c39b0ed945a\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628088},{\"amount\":\"87843690000\",\"public_key\":\"9e7399b01f46327e08176cb723e567f2a7e4d7e62a6e18ea7ad704c785a96b4c\",\"index\":1,\"global_index\":6690229,\"rct\":\"22b6c0391cf9b6cd6fe414f46e3f6a48d91b940f73354a58bcd7d285eed07378bc2aa891ea0a0b45836ad7603b35f60540572d0ec624343ad4933269465b9f06be809caed9b4136c21c4c4649638521360d693c49fe1d53d26c11477532ab600\",\"tx_id\":4935858,\"tx_hash\":\"eabd7d09be07fbc449d373bc5e839c5c2ee74602f7b1edd8f28607645784478d\",\"tx_pub_key\":\"d54bddee539a2cb41e88fb5daddedf98353a97eb6b44dcd0fc96c76722a684e8\",\"tx_prefix_hash\":\"10c3f97fd4e02739b7c7858a524e2b1d9a7fbb76a86ef9ee237a17bdfb071b25\",\"spend_key_images\":[\"6550a25615345084f31517461fd8325e7208adfd0c4e1287f1f0fae4e5cd40d3\",\"c26409c80943fcd71f87b254b21ea608f78b3cf659a3e644e12b9a73fe62496a\",\"4f8ac25828dd9054a12b820f29ed59d1b36b59c7ec49c8d5be24d15086d79a15\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1628088},{\"amount\":\"1000000000\",\"public_key\":\"6c516803e462144f7caf8497ba7522af2891e5b0ffda2d0f6b9e885f42a7970b\",\"index\":0,\"global_index\":6748303,\"rct\":\"5ae9c8a35e50b5b9972116228084a52c4cd44c08d0056036bb880de3562476cf872282031a8b77cb49e33d9dfafefb3a46887fa3488bf83cf8e8438917327609f6a0ea12856034562621a191b8dd6576fab404ebea6636ef1539d910740e410c\",\"tx_id\":4960151,\"tx_hash\":\"2a77480b4790dfd41185a0452d9a9b90b6ea9533dc5601a8c5a0f3c0ef627357\",\"tx_pub_key\":\"788f90292c40476de428fe871436853a78ebad8766215d95c3ab96f6855187fd\",\"tx_prefix_hash\":\"2b93ec015141c0ce22b029c45a743cf4a97766a5d198b40a7a7a080a4b2f454b\",\"spend_key_images\":[\"2fd8978bd1580603cbc22a02d13d435afd03f0c9726a7b1bc2c5364f3f3f5f3d\",\"bc7c4b9e4c91fb82440028e477ae5d2da7936a1ee78ebad3b3430b340a57e7cf\",\"4090eb08ff0c38dc73109557a41e3bdf043b10bfb587f4a950b04b14d4de235c\",\"f3ec36d95b3c10348c598347ba5240e7195e52ae59031a766108e3a5d3dd8849\",\"e0a3ff73181baf1bb0febfd83c97a9232022960b0a429866518ec94fee4f6289\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1631905},{\"amount\":\"84702980000\",\"public_key\":\"58b8c8140d067de8d78908d9f019e9300707f69aa18aba142321a819a35245b8\",\"index\":1,\"global_index\":6748304,\"rct\":\"9526adce2edf5127ef48a8f93ce7dab3f2945728d2bd5ebb57ccb39eb9fe642da2de01f8c1f4b7c4f88628cdf204517b85b53bf810a05463b4b4a9e8da9a660b7955d77bdebd3f3559b670d272e182ff79422106afcc4d643d73c89d4926300f\",\"tx_id\":4960151,\"tx_hash\":\"2a77480b4790dfd41185a0452d9a9b90b6ea9533dc5601a8c5a0f3c0ef627357\",\"tx_pub_key\":\"788f90292c40476de428fe871436853a78ebad8766215d95c3ab96f6855187fd\",\"tx_prefix_hash\":\"2b93ec015141c0ce22b029c45a743cf4a97766a5d198b40a7a7a080a4b2f454b\",\"spend_key_images\":[\"4c5785c068effff925af050c30f45a3de4242ad9126cf55962e785f5656599ea\",\"8ba5cf6aba304ed81b196c13d78f52e2aaaa6ccbfcf599483be174a46d2923e1\",\"e032979d743c7534f283d26d16a2786709098e2c71e6d77eb2e5a62c4a02282b\",\"82615a81533149c62dbdf268c6fe46e03603cfcb5dd725bd594bf3e206acbfc7\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1631905},{\"amount\":\"104278660000\",\"public_key\":\"4b0178293696b7515c1440b04cbc891e169f518b63938c511b7a639742f7ecca\",\"index\":1,\"global_index\":6748306,\"rct\":\"2c71bccf0876bd6e93c2c4ef17f7d0d25e25c75e46865c63aefe9f7ce6e3b313bb9633d2738b81b710c658f8f8aa105aa7fe5c6d21d6de3014069c48b0d4d90f30f40f66839234205376a1ae6037ec71ab83f611e7bd98083a8855aa6f40560c\",\"tx_id\":4960152,\"tx_hash\":\"d615dc03a17fcee27394bf18605bb33f6f7dd478fdb0b5e67b367cafbdf9c503\",\"tx_pub_key\":\"6f62aa5d691b7891650d4022b83cac6950c422c3944b34d417bd3b7d25e99f15\",\"tx_prefix_hash\":\"3f749164098ed402433466470413b0c8fb9eeedf1832a3489df7c84bfb41f8ac\",\"spend_key_images\":[\"e6caf77de94f9c29b2976609f8102698e4964a5dfbe51fb71d5a635735159403\",\"697edc63bbe31e1a454c8bad80484d73889aa2c1d1cbc0520a90b9c576a2aecc\",\"607e8aaa7e12506fdb1c7a776a6cf5b7e55e9ce029eb26c224f99c55f42bb51e\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1631905},{\"amount\":\"100000000\",\"public_key\":\"277aa77ec7ade9deeac4b3e4aa2ce79fc2f8660d2623e556d0af0a50716d0295\",\"index\":0,\"global_index\":6748338,\"rct\":\"842ec9720784a6523fe464ba7343345a4f862a5950e8f8c1781ad7b60627018c67729eb26fc8a510ac4afc0e8b0e3c281a63131f4443f08ea87aa03bf2594c06f3ffdf3a7c75f4db07a44b93b6a61f6dad00a90696f3d10dedd0abdcfe619201\",\"tx_id\":4960171,\"tx_hash\":\"80339049316b5a372897a7ac4eadd41caea810c25063ae298eda28a4ca1e18fb\",\"tx_pub_key\":\"ec0dc77dea51e188f95152e646258260f2e6d01049e852e8d1a43c23679c2975\",\"tx_prefix_hash\":\"92e5a0d6b71a9dd5a1810af4dc99effc9dae70bf8214f2b863367dd64ba21a9a\",\"spend_key_images\":[\"75b3cf561d75f18e9cb7de9b7d220513b7366f9c46873c80736bfed1e8c2193b\",\"4b09ec64a0ee0a4194c09a29d8bd8114b4aa5cfbfad7d3ac511a73d8f4ad8c9e\",\"356245c221a56b228f09f5cf8bf1a96e2c0c3135ba0a997c774d36bc13179f68\",\"901e924d3e9ddfb8e62775d266430a9c2243fd251c526a1e0c06b9c15fabe4cc\",\"f4d805cba6d4835547efb13ae7fa02746eb58fa46e83a75d5ae0e716cfcf0b65\",\"3308536beddb65c0b6eac4e1e615a8ab01ffe4d2e45a27c52d81ee0f528fcecd\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1631910},{\"amount\":\"7759290000\",\"public_key\":\"74fc75837ab8d1510887ea5782f6eee026c867483e80d20728544071eb573b90\",\"index\":1,\"global_index\":6748339,\"rct\":\"91820082fab3f84e1bc464b366307cb2dfa2317785e9fd7801c91334f00327b96bc74b72109ffb092cfff3790a392d39ef0397606f60ca9f9e559072bf8c6f0e0ce8e61bafce3d11c24471387bb53193664d791ece9c291331b4076cff0e0303\",\"tx_id\":4960171,\"tx_hash\":\"80339049316b5a372897a7ac4eadd41caea810c25063ae298eda28a4ca1e18fb\",\"tx_pub_key\":\"ec0dc77dea51e188f95152e646258260f2e6d01049e852e8d1a43c23679c2975\",\"tx_prefix_hash\":\"92e5a0d6b71a9dd5a1810af4dc99effc9dae70bf8214f2b863367dd64ba21a9a\",\"spend_key_images\":[\"9b94a89e32bdd339038ea4afe38bfc371dfbd876ea5bc90252b757bc4b6377b1\",\"be3cbc9a3f28814303b2365f28ec3048dc02be7991517539f1d9588c092bed6a\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1631910},{\"amount\":\"20000000\",\"public_key\":\"5f1e51a7a5666f732acea87d56020fd2dae6691ca7a2f57b1a2da2a7383e8525\",\"index\":1,\"global_index\":7002407,\"rct\":\"6e22c6205242602b5028c00ee4ff119a59aa6e3b5aec213d62fabcbbca4e4ad00bfdb79dae4845686106a74b9ddf1832ebabb02a1a81074900ab0f207ff2be0f931f9af358dbb557e3995d5a89643f935961d513c0c805725fc15053852be907\",\"tx_id\":5066112,\"tx_hash\":\"8bd44df0003b8cf396176355f4974e165d2d01cd30cf61dd4115ba8301b8fbaa\",\"tx_pub_key\":\"6acaa1671d037bcb558bfd7b1f38c81e49711b11bd272bcd4e155f0e2c0dd955\",\"tx_prefix_hash\":\"032201b13f30f8abdc7e340f18b349a1062832973bea8887557cf235c40d33dd\",\"spend_key_images\":[\"795e0a4df21b61087dc6015669d4633440e986425582aac1ff003592f96b8793\",\"fd9043afb3fde65471b6615f6de1bca2eb29401b12f51c054297a7749ff130bb\",\"02a666478d2ed417a3a1c6faa99aa58ccf96d1c1399ee473e2833c9c3cb08f13\",\"ec0084a04ac505378c9af4f8ac5d91200b44653f8769efcb5bc3e24047548117\",\"8d466efa7bfa4a425133390e070973c83cc274e5c0683009fb5ea7096a5791e3\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1649080},{\"amount\":\"30000000\",\"public_key\":\"6db7f4585d92d4eb641678ded716984305ddf8fe07e72be9ff0825c1f0fbbc63\",\"index\":1,\"global_index\":7003076,\"rct\":\"87d0206dc008f446fa64492f9fd04113a810eae4449da7041afcbccb97af275d0d81794a8e56634b86d42925f91703b262f9def73613c40bd9edbe4a74558507f66cd20d4a2a09556dd0d2cf9975cb070354e26786d0443fd97fc1949a32f002\",\"tx_id\":5066331,\"tx_hash\":\"2ecfed5b47987ab9260b4225bc88d73ce830033351c912f67d725d1d4c881698\",\"tx_pub_key\":\"dcf7f61282fceeaff3b3afdd07691aaba948c54e93fb800271d5341d8b990156\",\"tx_prefix_hash\":\"36e1daebbc2397b2ac1d5cfe82c211944642ee78382a51c554fa17adf113d1a8\",\"spend_key_images\":[\"d6c74b1dab22570ec6d886e12a438048586b74c8597e2ee629ef1d77cbac9c25\",\"fd9043afb3fde65471b6615f6de1bca2eb29401b12f51c054297a7749ff130bb\",\"e29fde11bca94255ff5877d2b12deae1c7b3b1c2da9e0e81a0b630d94b050325\",\"e3ed9637c203ad3276f3906270ba0a6b6871543e1b07867fcaa13b9017a48ea5\",\"0456a25d36aff7621b85cda0b77b8654c55f255f972e3525fd3dabdb79be39b1\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1649109},{\"amount\":\"20000000\",\"public_key\":\"14289645a4ef44bf70d234e7d418b1c84c7e1e82020fd686a5a222c309ee31a7\",\"index\":1,\"global_index\":7109509,\"rct\":\"d8e224051ec61ad6fe3c1d160ef1f33782d1541674f316241f9dde2ed3ff69f4bfd212fd2b55bc09bd3b32ffabe3e9767a51b19c804e301ecf36f29dc8149a0f9c2fad7a17a155e4dfd66b30d17a008ebf372492851d924dcc9e968f58035f00\",\"tx_id\":5121214,\"tx_hash\":\"0577a4489d4525ef02406ab6b69ee264440da71cbbab658116e71a1a5fccd87f\",\"tx_pub_key\":\"09ba796bf109fc845cc41957773a23c32698dfaab95e9f07cd1a968c85a63253\",\"tx_prefix_hash\":\"459be2312ffcdb67aa7c349d49baae9e2131ed4b190d3e5ce0c5ad052858b83a\",\"spend_key_images\":[\"df6fe2c3bef13bee823d669bfc464c5357637ec268dc4cfc89d23413e5006152\",\"9b44394273bec47b65ef4cb80f3bb7d0af1b98003c6b517a2064e30aaf2daea3\",\"f64d3c58912718629237ba7d29c63c8501a013b8978621f34f5769dea602378f\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1655467},{\"amount\":\"2000000\",\"public_key\":\"98eafc1b95f589515db6083ee306e915017475d8f412e5362169ed3425f1ab55\",\"index\":1,\"global_index\":7110307,\"rct\":\"5018be8bd881648dbc66ce5e1f0edcf10a4d49bda062d39151d0db2f30c5eff5cb7b8f8f4e08b6408d36a1cde30447d3f658fd81dd490b20eb5e5b6d6a45190635162e5b51fb3495a3995a02e2fe3a48734be912253ec2811c86b337cc51ae08\",\"tx_id\":5121563,\"tx_hash\":\"5b2eb039b9b248214a2784f0978f5b3d344bb80a072f75488e71bfa42118292b\",\"tx_pub_key\":\"c19c3ee028843bcaf0ff400a08e206f3345443a7137dd0f108178ffe47d1dc4a\",\"tx_prefix_hash\":\"53a92a769f50ed2290768a8dec5a31a5d71e098e1048d9f984e861b01204435c\",\"spend_key_images\":[\"7f2f5b5d20d0bcaf84aded3c1c7d330401cc563a157883f8d1194243a9cf95ab\",\"2aca1cd95da36a72000254f790e2f928259aee7abb11988ce875eb262ee017aa\",\"28cb05b8321855d283bc6af9387e37ac945f624f9bddea8a16a605185172529e\",\"af97af2b4435eac06339cd3ad69850f3ecefa35b5c23d576df4d0849afd37eeb\",\"8b1485f877de01dcd91a2c0082563241b609830798b893503547e5c3ca1d49ab\",\"184cdb358da3a2ee25152116919702110c6d201e1806e3a76ed977edba16df43\",\"5a5087433c881cef1faa0d76f2c172e510cde09175c3ecdf034d68c1b20648dd\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1655520},{\"amount\":\"20000000\",\"public_key\":\"de9218c7e81d3d4ee885944f5232d118bae11ba1d4e5803114ebbd39d988b378\",\"index\":1,\"global_index\":7112535,\"rct\":\"4929100b74c0c968629d13e76cbafe79e1ac9616ab8e57def7c968b54125c1907523ed8106d381e7009eb29d2f32db0c1d2035471ebb3cfcc13b951c0dad38099ff552a80ea7749449e135e7da288d67dd336debab6472e69d5de27afee1c105\",\"tx_id\":5122415,\"tx_hash\":\"7d0fd684db587e1ddf0960826c316e2326b285b458ee6862787510100337a7ce\",\"tx_pub_key\":\"9863a9ec268bb378fc52c6a65cfa81cb4d6964f4db55ec3ef8f575bd8c6c8e6f\",\"tx_prefix_hash\":\"9731cb75026a743d1a43f4c20571dba7b5541019bbfe6a7d761255bd5dc7db82\",\"spend_key_images\":[\"2f91f85f26261aa9ccfc5332d9a2f12532598731d0aaa7627662b6af91c36f28\",\"8e6f624b7aba9363caee098898c784b99e7ea4b4be106467a111fb6b59e4cf34\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1655657},{\"amount\":\"20000000\",\"public_key\":\"0df6343cb4f534f620366e08f35389ddd7a89b7d86c97c51986440f3a1b6e8bc\",\"index\":1,\"global_index\":7112669,\"rct\":\"a211c23d7011efeaf5077cb49f6daa914f17769fe6891284a9e38ed0a61d08b8a51c6c37c117b4d1118e072fe81f673f98225fcfda51e0e7732450286cff0d03bdfca6a3e591efccf59a908741234b96a974b70ee1ed495a052a5a9a4f13ef0f\",\"tx_id\":5122474,\"tx_hash\":\"a263a1b174454908d3b41f0dc763e59f6ee9bfa00ac085095ce6909e8994857c\",\"tx_pub_key\":\"4ba97ac89c45d4e7ef262322073e27de30a43037e1b4713286cbc80377e0cd82\",\"tx_prefix_hash\":\"4fcdfd7dfd3ecdd6afbd695df4b2a0ec036095e9ad0de85ee014126e688a835c\",\"spend_key_images\":[\"3189ac5b26a47b9b5e3a32ababf54f300da6230fb979403c61266d1f080effd0\",\"3422aa0cc6f73b3ce4f975031ff20a4102ab1151535fd63f9c9e2846ad611600\",\"55bec44ada67c10282378982ec00cb488f7c9c6fcef0ed90027fde3bc375518c\",\"9814386baea155d38eaafdfeb2a5acdc90e91e042bf20744174d99d5642799e1\",\"520b285d3d6f187d1e82a52609e1d75095bcbb78964ca857c33d7d3c513ebbe2\",\"ec8911602bcaadb90286cb1ad0fdfd0f110b68f36d129878470e6bf4d884ef34\",\"8ba64fd7d880eb412bc6dad6cef4496f48305043d0cdd133dc2a3645b61d98bc\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1655668},{\"amount\":\"1000000\",\"public_key\":\"dde5f6789cf3e4af6f829d0388ba7e33414057af272996db081938ae16e237c9\",\"index\":1,\"global_index\":7113000,\"rct\":\"befe2f3c27cd17cb7e189cf380b67e59a08ce17bd14b527b461ba498c5d64260a1ba5fd56a8a1e6dfa1373faa3514169d81fcac9a1e5838c3a0c5f8ccdf866050dea209f4204d4dce22c2f039ea4e4fd3d915f123a5e4583dd29d047f6709104\",\"tx_id\":5122625,\"tx_hash\":\"8e95a2cad2386aa57e60d4900a12fdbd081726164dffad4c2203ae8393141b27\",\"tx_pub_key\":\"82b46de9280ab9e9ef862c1c04dca0cada131dbf995c292bc8dfeba105a79e11\",\"tx_prefix_hash\":\"edef4017cc8ceeed87af166acee82977bdb5a5f9e367c9affb16611fe2ee886a\",\"spend_key_images\":[\"2287249daff4aa7e81030f3942c54fe2c47f76edd08c5f904a15d55902b173b4\",\"791b4085f4ee1888fc8a5d153cc8feb579ad0a48429e7435dccd5b20ddddcea5\",\"dd8e7e561154cbeac5341e21d08e3804a97c21f52c65d964d3131f1969d9989f\",\"034288f887e267689ed842e8c3038ca05e1ac887abad0ce78576e4f52d85aa63\",\"fbd7b8a8c137fcc0a013a6912834420da605df4bfb20ab25de31eb3511489a4d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1655693},{\"amount\":\"30000000\",\"public_key\":\"d93d8261667504d7978f7bc0551f8197b3634f8ad951443a6192302c9faa2b2f\",\"index\":1,\"global_index\":7120611,\"rct\":\"5a5efde262454aa3f7d95dfd5a6ebbfaf5a7a0665404a58599d64f1d42080ddca31e33a9a73dce8f0b1e79d85becd22eb76894960ccbd5bf2efe5dfb8b4bf60a2a0ce7109bb44dd56807c89af375d990394189ca8989442e9afc5478e9971f00\",\"tx_id\":5125915,\"tx_hash\":\"5567260ef6fed56c7f51dfcf2a3bd13104f65c8d5842ae339b2f0193d3fd7575\",\"tx_pub_key\":\"ef2dc28c65dbc3f922913b71ad2f62abf38ae477b0a12c59a31fdff0ca311870\",\"tx_prefix_hash\":\"0bcdaf109f3e3ff63e0b6ea32043b5c08eba03966e8f7d8c54a29bb46b84dea3\",\"spend_key_images\":[\"028d6a0fa9790ef05aabd75a1930ac52fcc779d18221da56a3c450e27c613cd7\",\"a77d29b404822ce548bd8e981bb0c7a18628606bd119e254b993d80317d4345c\",\"dbfdebcabd1b3f2d1d7d91c1984c9e3fb682e15dcb1f40f561a5392ba074a619\",\"405cd8802aa3c8c5160f1b95249e27dbec02359fac93906e160e88672557ea33\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1656244},{\"amount\":\"100000000\",\"public_key\":\"a485ffcb9bbd762fcff2702de0b557ef0fbcf1a7ac146a4094d91dd64ec529a2\",\"index\":1,\"global_index\":7323835,\"rct\":\"db2e42d9f783dea3f70fdb460a08ef96473f7a3edfc8fd557760ded8640dc936f70c0f35cd5cfe295bc2865250342ac4ec9d60292fe0d957b4958270e49de90eb94a020f0847da8108a825cae326f64a943f9bd21ca675be6e3e1e99c056ee05\",\"tx_id\":5213233,\"tx_hash\":\"e5ea81cdc25a73a8bf12d75438abe53f92829ba09aa99ba78b14740e05f540be\",\"tx_pub_key\":\"af0a9143a02553331dca342011298b3cc5ce7932b353705d69837b17d10d3d5e\",\"tx_prefix_hash\":\"6cdb12a200e656e6e6c9f3ff801016742b8e6d4cafed9be2aec4119973a78de3\",\"spend_key_images\":[\"42355a5915df6c1b151f50c328a12fee24cab78caba9cd7ace0a3ceda7762b50\",\"7dd5af986aa9ecaf92cb3483c9a7f7fa0b50c1ea5d579f654aecc9905e496c8d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1668436},{\"amount\":\"300000000\",\"public_key\":\"1569e9f889781fe966bcdaea21399be3e1413da9fa8a375b57a5abc673f68c53\",\"index\":1,\"global_index\":7346554,\"rct\":\"742cbcfb61d3eeda53265cb0a472cbb3964e63c78f4404443776269d45558a374ccd1ebddf6eb622e79fac8c6b9119bdb8449c5252d55f8dd79b1d36d4817c01a242edd55f211cad3cfd70d11226758ec2229cc3639a3c88537ec29fa496b704\",\"tx_id\":5222968,\"tx_hash\":\"bc5afeac3449debe4b4de15df0080e3198afc63223fe96f600330b8e39320f1f\",\"tx_pub_key\":\"15e6515f52d2993c0352d71524c5b49f853651c1adeefd3411ba1a5705b7cdc2\",\"tx_prefix_hash\":\"8bb51c3704ff1066b46946af31ec78931757ff9bf1d2fdd273748620220b58e2\",\"spend_key_images\":[\"39b1aaf2248f43b14154e059852b37b5905ad61dae41f2aaf853e8844a54efb7\",\"6a2f8af52929d76d475238cb45637f0dbf315c20bc773da9b6b4de1af4054ad8\",\"2a58036c505329c1b740755e7628e0eba762f2710ff191a85f1e8e4c552f599a\",\"886acf51d44179e4f1627d6f352bfc8a4a7f1cbfcdf9978ab8a30184359c987e\",\"6af9e698de9911a8c110dd9201ee171402befee94cefa5be4a448d8f3d0ca022\",\"b7fda67b73595f4d21f8041e5b09c6b2c5fd7683ca5f75d8387b1f8796112f95\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1670008},{\"amount\":\"79314790000\",\"public_key\":\"ae5a59db59fe309cb058b1a7c76fcc8c2233da79cca1fceafe11f6e55bbed377\",\"index\":0,\"global_index\":7346866,\"rct\":\"d2046e7fa72d78d93b3e8c88e360183605c5ab8502e354393712b02dc5d488e6bdf4d58118d0be36daee27817a4e7d736f460d2f1eacb56a00d086f9da98c109d0575fe8a17fdb767d3ba065064133f2cd330e69317636717fc46e59f9b17a06\",\"tx_id\":5223102,\"tx_hash\":\"e8c44021ccc271b63aa1f6283a4c3ab386761776f50bf68d5fb0b80d5f3260fb\",\"tx_pub_key\":\"09f14419241e03c83a17f16e4415f7809c51d0668270bbbb79552a8acea0819b\",\"tx_prefix_hash\":\"afdc4d3510dc1f13d356538f2fd44dadb7b50396054075ee1bc7872f81ee5c14\",\"spend_key_images\":[\"52234c2bc15fa666d611a22a7cf021755ca650ee69faa5696c364491a6881754\",\"83da3ef35aaa62964709fcf1bc0b517922b569508761916c7b1bd0dd312e87a0\",\"802c2d593d1e7c42ca2707b9ab2f2e9f3011374d3628f1850702b2f7bb159bd3\",\"9ebede0f797641269758f692d17b1b25aa2efbbc91177d3777d23b7154396754\",\"6a7a9f34b15935ceb8e468f7855c1cebca2844658ee9e79d257ec86b1a87fb51\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1670028},{\"amount\":\"1000000000\",\"public_key\":\"14db00825a260f432c9cf1bc52cc65965e76b5519b228bfbfed2ce2c3119e73b\",\"index\":0,\"global_index\":7348866,\"rct\":\"f18df9fc7363f6d92c25716bb18e2428e4712732e2a67f24ae799406e5d1e90f739658d1831a13fd92d30db16a615624897513c795a62d29166756f5d8a4ca0ff3842a5578d04ab559f2440e4f5c9fc2dae4033d49fac5b57048d14a054fcc02\",\"tx_id\":5223970,\"tx_hash\":\"e789066c6fc45cd55cef2a535bcdc2ef138dadb07b5f61210c23b3c6d5bbe456\",\"tx_pub_key\":\"e0d953678f4ddbb39fac96a739d3a1e7ffaebf5f2e5f69b6a064567eb3c053f5\",\"tx_prefix_hash\":\"d2de36e2019bdbdf63891301a1783e55cacc8105c6cca8f4b7e39620738e251b\",\"spend_key_images\":[\"11c435331747d5c6af9ffea9863687c5b80ee5af19981560bc37c49623b3dd30\",\"26690763e90c54564fce947af4c5ed7cf55cd1c58677619641444793a40db932\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1670187},{\"amount\":\"330000000\",\"public_key\":\"f628f516cce1408ebfca9bb3a144ca044dd3f2de19711cc42fa4bf296b6761ca\",\"index\":1,\"global_index\":7440388,\"rct\":\"66fafd6d2a1d6e92e30ee7fae132bd24116c325fca4594225fdf6f40cebd39b386ec21d9bd200c6212027e79237ad5fc076caf5c35e625eb2eb10b82debf5900cd9b8805d566e1ae29f69672876921c8a0ce0c7c4d87cf52dbd483403f435c0c\",\"tx_id\":5263291,\"tx_hash\":\"10d0b955ef6e972ba130f44f36c6cd52511796178346a8fdc0ead84893981af6\",\"tx_pub_key\":\"d067e192807d4374aa7e8f832a0702b2c6f35fa30a5fae43a9ecddc3fde755d6\",\"tx_prefix_hash\":\"eebcff0a7b896c782bddf3c988134f1db4562fa8d480609e401e2a7ed30ac310\",\"spend_key_images\":[\"c63ba1bd102765af590144c5ba1fdcdfb88aa0ececeff1ebf2380eac6039b4e6\",\"a993e491ff7be30a8fe89b93a9826e56aca7553bbcd6b4a3a52804f548bf792a\",\"153e02fbd866f42b95afd1121c159a90dbf93131ebcc437060c6b094d584be6f\",\"d581c6705aa55330f4eb68c46c8d0b0779d99ff7d2e42ead8bf39aac7afc7a88\",\"c03373d54780b113414ee2f1084074dabfbd1394f48e60682e321fbb1d4c79d1\",\"3895839ac1eab3c4874806639d9a2bc8888f26b83b8e563265538d7c16cc9d8f\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1676593},{\"amount\":\"710000000\",\"public_key\":\"4b4c3fcc8ab73628f298dc75fa5976e1812cd21bc77f30bfa6bb2eb6e713d2f7\",\"index\":0,\"global_index\":7440663,\"rct\":\"6b560a85f4b5ec7b4ccd4401717b84307e2b03c646340708028a6d97f41790e39f13da5d8ccd642d5693952a3c67b78ff297c8d718051c782b3f37ac6010cc069938fef32ffbe626e18685b7c13c17b53d3077f5bae52742daac2f29b6c9e708\",\"tx_id\":5263409,\"tx_hash\":\"e8d5323f3c05e9669f4b078efb480624f31c6dccd6b12d8fb940fbf2c410790a\",\"tx_pub_key\":\"976feee1972bbd05d6ac7d52ccb30614143c31021b3941e28de2cbb1f48a8ddf\",\"tx_prefix_hash\":\"51d3d06f34d4f8a927e7def6e319ea61a471a17681e1ec474bfab51fe926deaf\",\"spend_key_images\":[\"146625487fac0e89bffd833315081ac013b03fa91cfc230b4f258a35710c901e\",\"7fda638515c8a44059c47c005a5981d3d846093c2841fb6e4e9ac2fc17393993\",\"0d86a07155e6bb1bec2550483fae29f9ced2d982fcdcda891673da82300cefe9\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1676617},{\"amount\":\"200000000\",\"public_key\":\"e92465cd124e98b3741b93d00346374eaf1cf37d3670eb21a595047d0b12accb\",\"index\":0,\"global_index\":7460517,\"rct\":\"9b59ae166065aef95ab4380e0827035ff5ad579a5b11e5bef305af5369e61d4a9b91bfb770cbb9ada6b704d118417724e2b5d8d208c13e4bb3af9a355f00500e48c770addbbc0fd595d0b1edf36b591dd58102b100140146e7d93371b01cce0e\",\"tx_id\":5270924,\"tx_hash\":\"2d9d9097ed6ac786e5697a924f69120f34efcbb5d96bddb5373710039848aafc\",\"tx_pub_key\":\"e6bea5eaaff6beedc54dc5d4d24883fc18537af58425d584dad6d21fa6e1f27f\",\"tx_prefix_hash\":\"0fc1f7c18544cae3ad13ef8a5393455d9f5057c1e10d6466b3d1855d5b1a9a66\",\"spend_key_images\":[\"5f61e909d1100ed3f88ff28a1fe2e42bb1892a2af55ac77a617fec2a12ae29c9\",\"6f3f575482c5d3af544fc3cb724561fac8473cb76c830fe3e0a1674cacae9497\",\"77f075eb362eac82e5f6d2d0557554f7216cd38dd40455fc75feaf073ba5f623\",\"cfb6d0d17f1359edfe119b4a596eb838255f8a5e63d8bac943b3eeaec3a54ea1\",\"e67e0554e4c73393945fbb1d04b6db31ee980ca5d0857f93d64c11965dc25239\",\"d7617353121dd0c52a30617a9add28982c72c6c72eecf02ca539a1bd1b613982\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1677987},{\"amount\":\"1337000000\",\"public_key\":\"5f871fe678a9dcba8ef682e8f7362cea200f42696c7dbe03f902ca19173eb147\",\"index\":1,\"global_index\":7499194,\"rct\":\"50b0100d12c4c8824b3f3a56b97feefa2b0829a3fdeefe19b7d6ebcf7b768450eb4112e86debb0d859da4c0c556c7720c5388eead19863229a3fc610c23093024d8bd6f881687518019c8cd7d61a40f3a7486546df4d318011eacd34f4b17b0f\",\"tx_id\":5287448,\"tx_hash\":\"bddec2487526347949f63200a98516716591881d29670404fa15949eede6bbcd\",\"tx_pub_key\":\"1009aecc5f53f75b0731e0ccb3fd37ba2808a5c645a2a1f56861f121c926e4b5\",\"tx_prefix_hash\":\"7b3472f417eb0ff0c2d12bda7c0ac498dab0eb4ae05e3ef8314be6d07a1b719a\",\"spend_key_images\":[\"7c63f330b5ce0be49191f5777d2d4a635761484bf6ad98c7427fdc1529417183\",\"0c0b1dc2ea8a8b934a8afd1da03eedffcf79ac6403011a8201feec4b34867e97\",\"08571a1b2b90793b74b1b2fa700d8fc32cc44573da1099da4a150d17f5be4441\",\"e87a4beaf7151b4e1b45aa1e054f2a539521ce5eabc0362baf34866b79d6800f\",\"d9a2b4b951612c0b3888f68a516a2f97adbcc88e7e075deab4322312ed8cc792\",\"fb9c867beb4dc3d16e28e08b13e0dcaa02aa15e7307fe68388858da767b1d825\",\"43251fd48b890024334210992764fabe91832b271f421daa9d88987c6b065797\",\"9307b0960eaf4da4c7021db0cc1303062c364e22bf9366add175e7da72d45523\",\"30738835ce4c269f28be6cc848154c0753918761315d793a59be9928d550b95f\",\"7a365d1171adf97ed1fef13b9d0f542eadcb09cb47429cee3e00d8279a2383df\",\"e3cc48e3d8e4c6e3ac60caf6703aa3a37c555cc09c591d8808a3a30e7b6ae6cd\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1680752},{\"amount\":\"210000000\",\"public_key\":\"89eb08cf704d4473a17646331d2c425307ef03477e5f18ee6a31a3601ba9cdd0\",\"index\":0,\"global_index\":7510705,\"rct\":\"befe623ad1dcae239e4d9d31e3080db5c339ea8c5c2894444966967a051f27839f1f713d6f6bdc13fec3c20f78bbae6cf08ce185273fa6c913db6ae1f44e270ea9dcfa48ecbae364125e0c4b0cb7a11fe6c250ec9aca1a668a0708e821d6550b\",\"tx_id\":5292354,\"tx_hash\":\"22fa4aaee9399901ece7d9521067aa7791a727ade2dfe9d5e17481800ccbc625\",\"tx_pub_key\":\"4f151192723d3d45372b43e4bf93df8ad7ba5283513c09226fd0603c60683e00\",\"tx_prefix_hash\":\"689580f0804eff0fd9bd76587ed9656e4cda8e70a33f065b5461206bcf9051b7\",\"spend_key_images\":[\"f7d36ec87a598d5163619e1a8b9280331df2d1e91d2b58c718a00271d74d1f4e\",\"c8596d5d876b3b5d1f383e8ae04ab583ee3652a7da0d6bc0e0eddd0385ce22fb\",\"5f22b456c60a095c5823900d9e842002cc446be4ae6af3924528d7c2d5f5a92a\",\"ccc3784f5801b410f01cc9c6368281c5df0f701239616dd48da67a29a692b582\",\"dbf1ae9be5a6dd81deb960007752bad70e71b24ce9e98a80d2ad5c63914c9c3d\",\"7371a3f7508160166126652222c06facf9291177d64e049103bfad1247439522\",\"75f1282390ee69473ed87cbbb974ccfc8a8f0009f0450aed62d0da1f2575d9fd\",\"6bc9ad256231811c638d411c26c130ca8db6db0c7adc2cab63312f2a1b1fc1c2\",\"ec3178c21ec5b7d9882e412edd69f63a60c9cba913106dd25101c0f22e02df59\",\"108b12ffd8ca99181cc62fbc5f3fa6d3cfd36f56dfc8350397fde028e75b55fa\",\"87e1ecf422d8f51f9ec988f6e413e33643251faef316d2ccc999c47b9a445a46\",\"38dbe842975a0f70c2fb6b2f375fefc84a8a2694f09548b7b0d76e181a035d7e\",\"7944fd938a0b9821c7ae77924cda5235f8d9bd6fc819156eceaa2eb01bd3ea3e\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1681636},{\"amount\":\"2000000000\",\"public_key\":\"90e5d9146f65d550ea34b53e603eeb209d1d98ddb966522878ded9ae878be480\",\"index\":1,\"global_index\":7551355,\"rct\":\"33cbb12d60df2b143405e6f479e0ac83e1ce8119fa988e7c6202cd4a470705d907313dcd63470b43c88750ce48080dbd6dacc768e88c8c87e460ed9bbc885f0b9d90b4d973cd6978618061c05b8b64f2b2f9488680b52c791577ae1a4c4efe02\",\"tx_id\":5309375,\"tx_hash\":\"f5df119d586c305c926642af7d6608c8241d345da90ef65c3405da74f7feee3e\",\"tx_pub_key\":\"7ffae907b13a1f0cfd82f9c2c1b16011dfb5b3c689d4888a87b706c9476ea480\",\"tx_prefix_hash\":\"1734332ad1278985be2ca1705352af09d25caedf20501f5ad8fa5a313316c4c5\",\"spend_key_images\":[\"06edc3bf02e3c3c49182c87d2f17c3b1b82aac5394bf92ab49d2919e8a349705\",\"6c877425a305bb8902542849c5e2e92e5015eeb8ab01be0be5ae26b192b9bc03\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1684429},{\"amount\":\"230000000\",\"public_key\":\"f659694299d97fc93db504122d40dea1681a896567933635dc6337abc4339c10\",\"index\":1,\"global_index\":7551823,\"rct\":\"dd06d546553044cda0f083fd189cd8ad93ebeca557169eefe1e34dc48c6fac27110a3ff8dc24a61b595a03a034009a6d1f0ced61f19fb6e0d7c2b1a67bb39d06c7d5713e0a394551ec978b64927802f9307ac29c8ddec3857f551b945ef6a407\",\"tx_id\":5309604,\"tx_hash\":\"05704e7402d1373d14dccd383e4071bfae0c2af6eb075e67075b43fd7d26b4c4\",\"tx_pub_key\":\"3511d9117fdeac0423314827188aa187f1eb742a44ab0c01390053b68b00909c\",\"tx_prefix_hash\":\"1b89ac0c818454806686073cd2d6bd501923d6eec2c0e54e300e3ae68a2c5344\",\"spend_key_images\":[\"557c342782fc21471254f304a3351a0221cde4e17b491a4eb7dee5ffa79acf8b\",\"6c523874c254b39399587fb65d01d15c29c442186c0147d8b68296302094140d\",\"ae5bde1ec45cf6e4ef9b5aaf052571385cce79800ccce31dec8c85752369d148\",\"94a737c08b1b89d51ea5409c52b09f5dba759efaf6183ab1798b4b3af4dbd3b1\",\"04f10b1f97e5e9f5b22c42a99f901e06d3c1d0b22e5d6662938121a08a37a003\",\"f3a56b0cd715461c4b4d2962284ae968eaf510e58bd8a13070be2a0097a8eb43\",\"5de591d69a39054ce9e63444ae7f38559823c307a6e1fcebae73a40bd36fdf03\",\"809f098ab25d828836e5b2bd31391c260fc9307d06275ba954c234b5b6d17b4a\",\"373279f29acb6df49bdf28b84c1f4a1eeff2817b68f7fc9d343bd150e6692383\",\"2360f6a4845633a1a7b52c0e7017239cc04d9247e72d6d19b93f8fdabf6c8494\",\"cf637966ae3793376d396bd5d960f60e3be1392d83ba566388dabf4c609961b8\",\"7c253871e6f86072016e8bf9c82fddb04ef3a8d7f655a70f64c54043c0915b41\",\"529fdc714905c765fd4871528f9de476a5cb2945195e9fc8b8d74301f33030e1\",\"6ca4bf5b4aad97020675141b92f39ec38e5d73c06c1a2550b3eebd34941bb5ca\",\"f7be38b09f0edaa0b42f38aefe763da1bb7397894435ebb6426daa487083431d\",\"eda293733029331e31ed32abf291df95b7f6147389f18936eaf40973a7b73d8c\",\"eb05178e19c9e348cac21ad8de13fc883aa3f0805c066f37f0a9377cd2bfda18\",\"c6f9ef0e28bb83d7b849d5808201b9fe10e6edf8051f439982d1b533b5fc9ffb\",\"01b961a2b1c27eb995020e53381b14932a7cbba85cfbbc359c0d932120e3d3af\",\"6ea875a6d2e93ecc91bc39859be48dc1d4f9ff28cac088000051a684a6e1f330\",\"178b24baacf1bfa8a5c668da25a69cf2ba450e3e5afddbb5e1b59c08adf65fbb\",\"f7ec8aa1f3c0163b862f163e2905dd8a0b70209572dea9d602c66d3227ca8e4c\",\"173b4ea1335a3baf1db8d365a26195c9b76b345fb74a20df3ff22c0c33a30b8f\",\"83124e88d43c443220691328e00ac41c5f665a8a78f97316e9839a8c4438e17d\",\"f8cb43f8c3f96238f9c5b9384ea397ae5a5cede44a11d35ae98a07a78fef8be8\",\"63def9f3d5514d42c2596ea39f38a232f0e032740c4c21e85d64f14edc39adb7\",\"0035fd499da783dcb976e3970340233cf2e3e3e967c393efbf4d01b2fecd90b2\",\"bc8747890dd1727394d7639fa2ec97b07e70b43cc48a9aebfb9c9d23aff89e96\",\"b902347f23d92711be3fc1879b2267113d3478d2b4f4266d290061670c8288c6\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1684479},{\"amount\":\"50000000\",\"public_key\":\"6c0828f041fd3383b4823bd619fa9d130b83da8b10aa81bec1f1529890548542\",\"index\":0,\"global_index\":7552032,\"rct\":\"eb3291bd81992ec300e94e8f1bbf0bdfd7bb8b8ac5e1969f985f5642961e30f1bfaf72e1a284ac62da47184165091e2b8673143f8b5d533b9d2143c9e64e5f091a14169fa79f151579eac8e41102244aa148b6142121f5ad1b85d6404c04fd08\",\"tx_id\":5309676,\"tx_hash\":\"22c79cc2e5cefe5b1ed608021efc281f0eab6dbe4cc11051d59cb30b367a5120\",\"tx_pub_key\":\"471fe593e98e65529eeb2b60ad23ad0f7f879a51ef0a41ed34bb371bf346663f\",\"tx_prefix_hash\":\"6551844de3ba9ca5c0a58a8dfcb3fa6b74439c0f1054563ba7cd9a5eee26425d\",\"spend_key_images\":[\"916bb1f0f3dc1372ea81bd7f72b79f164844eb92bae67ec024deaf8dd48318ca\",\"1de62d56c5af4b4130a9f6d82312cab03eb245ce32454e4afa65c1cd9b6a1abb\",\"0c9bbddb03a7c4aed5eab1eb339e0dd8788584c557e146b73f052951c6aed68b\",\"eeda7f5391ee3017d518f8d26ee75e73251aeb2d64cc01c3e57e58c69264de18\",\"bd5933c46db715f1dfecb2128336fe52c1c2f2107f69403217db540d228ffb59\",\"0c4283e0d7bd6cd2455d30850d74f753aa0cda93f524e115c20494f65599c572\",\"525f5b1dd6193ce191654dca4e06d6ae001cb801d783909658a02d5948d8914f\",\"6518ea4175dffab3d3cc49c936de3106b026187eec88d5dec65caca950566c8f\",\"8bccfc4fab78c56e97bad72e45d5ccb7734f4ca6566de5218b903d87edc027ff\",\"1221b9a90e422f6ef825cbe08dfc7a42bdde8e9e05163711166355aff9bee7c7\",\"2c7033c0441cc4d9f05721e6ac2e706fc0b142039b4e69e200edc1ca6e4012a9\",\"3245ca8cf336ef932d5734eb67fd99ead253a698bcce4a843cda409240b06245\",\"96074da9aed49a5b703749d5c81af8231854a7a08839c6f819609913d0a464c2\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1684494},{\"amount\":\"100000000\",\"public_key\":\"2721b9cf6cb9e4227cd4c58ea73be9c6e6ebf949d07e90f3cbfc624a18c91933\",\"index\":0,\"global_index\":7571542,\"rct\":\"14972c0692f37de21d4fe2e989262aaef574699258812b39908c6f9f28bfe80f07cae2373c7419eb41bde8425107cd3d87dd0211b1a59e92bad0b09789109d06620a1e4f80dbfa4ada1d432e55b3c23e965e858bc04effb64c473de0da3e4f0a\",\"tx_id\":5318071,\"tx_hash\":\"33fb202b7e1b2382838f17e5078311944870197536df0a560d73605023befcf7\",\"tx_pub_key\":\"3cb2a8fc531565dcc20477ec624fc1ffd60af9f491ab4ec5d54d4e4d6441d0c0\",\"tx_prefix_hash\":\"ce7bec7db0171da5e345103b7d38cdc19fc1db0655e4de8ecbf9b52d11b0ff51\",\"spend_key_images\":[\"064eb9231febc71fda8a4c5ee4b6555258f4ddf1adb6058719e8c78c8fe7b82a\",\"2dc6d91bb7fae890a17273d431195dc01e688e62fd6baf0758eaf62877d59dd8\",\"78bd1705aba7a8980dd8ae8ce5be027e12e1d5188299063974283303016cfd19\",\"72be14e36ce1f27e6fa7f056ba69020d3e419a2cde6dd19373cf6a38e7c487a0\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1685790},{\"amount\":\"1630320000\",\"public_key\":\"437e101b61a526098adc98e46c8a674d2b3af3b79cf6ce8947e4effa2b545069\",\"index\":0,\"global_index\":7571614,\"rct\":\"026064f4989c3b19d99d4e3902a6800cdda39127449c639d0d9fcc31d9e4b297211cf6275f64d613cb7b553be07e1d738f72b138c4eaccb91970a10c513f2a005471ce338c4f3ea6bc07a37d10c32236af28c0e85d39ebdf8aa37ce2b9e5060f\",\"tx_id\":5318107,\"tx_hash\":\"19a98217e48c4db9c527dde5c7498317e2a6f258e31c87c3fe8d872d695b44f4\",\"tx_pub_key\":\"95c66b323352e10e7eee3220cc328f89b1b9dd5bfd2da4f61ba5dfcef923722c\",\"tx_prefix_hash\":\"0e053ddb7e60a64a8b501525963a61d8c182f82a66933486e77233055dbce3ac\",\"spend_key_images\":[\"78d989a085c89ed88d8a00c8cb2873d340190b4a5d2c56bca7bdd98d1ab674fb\",\"12d788fc69109ff777348bd4bb315361512945e24720d5bf4ac02d9803666834\",\"e96ca257967f523a06e7d7963774be96b9dbe0e3e953eb08fd2d5f7267eef756\",\"4c337204918c655f38c9e04abd116eb1eb332a8d0ec4fbce30c6e597fd41163f\",\"f2bd3d1de1f5b8c60cdaeaf09f3b0bd92378ba00ea62ae0d7a74114f4e662ac6\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1685794},{\"amount\":\"100000000\",\"public_key\":\"6a5982bf097116b68fe817abbd31b95821a0d851ac8e4ca34517b1cbe4449501\",\"index\":1,\"global_index\":7571710,\"rct\":\"6d8cd50a778f658b5e2ec7e7e1b8e19e80bb2ece759ed5e40398c33e5983722e45078078a6195d92c3f83d0f443d178a31156702c42f5c4b3e897e9931055f07173349088339daaa080c1f747a9025db0baa60b12beded6c7bc8ce893bda1700\",\"tx_id\":5318152,\"tx_hash\":\"7010c701459d2b897abbfed8f1dbc60b84c4fcd111afd7fcaf60eb1167c0a7a6\",\"tx_pub_key\":\"9321878b374c7f40021635bb03ed966217e5b8e7eb3e125839c55ae48d04ef81\",\"tx_prefix_hash\":\"edb575b5fd86b3e45214742454a4cfcc3d55f1ad457cc598c290dd69d9ebfa73\",\"spend_key_images\":[\"13207c1382f9ee05ddc9c064667e3d9d4cdf6969e60707b91c872f28dfda5110\",\"3ccff9fc11bed753205b8a09e60b76645b76358458eedbf4958f3c265aabfbfe\",\"91eab919b6aaa08381daf1fee28bdf0d28f549b846a3a8bf287c19244097528f\",\"b59175425a57ae3be3512a0c8a00d3b45d28f13d25e26794051cf1bb483ad987\",\"dbaed1e5b027e771fa2e6cd6a7971be81d4e2acf46e1087f4eaa57e4bc8df07a\",\"ecd3fb09f5ae3c4d9d38e1a0446c77889f9d682f8346067e6c789fa988d5a0c8\",\"f5c7a56e181b812788dabff34bd2f71879c05b526b185984b4a9e9a9d87fac9e\",\"f9f61f80f3c2d0a19487786c960aed5c191d9fd90f52227488d0c8afb88e9807\",\"719b4566e21fd647e568fde36326f550463a209ffc31c8ee85deb41ea0b1b68f\",\"b72f3ca68032f5d9070068a43fbeef86f71609033574967a8125d8d6599ebdfd\",\"fca49912b17e8fd8bed0a2d99c255f2e0c1c42bc6c3872a27bcd7d5b060ad847\",\"3fd294d6561bc44c7eb2483aff5b05b49df2adaf78d4c245eaf2bbcbb4d7037d\",\"bc487e49422797b9f1032d799db71e4d9e5acaf4dc3fad1950e6ded3fc3ee65a\",\"082f0e352236be01f3a8db1f03b196a45d978cb4b8a44166d9c4aa2296f0aefd\",\"d6cd2f30766f70a19e7615e7bbdad40dcbdfb9e37388cc1bed3eca9f57b1ea1b\",\"c147a39f2381939a16f48105b9c519228c59e6be759f76f7810090ec78311582\",\"2d83acf0c1dccf5260475f40e18cb3665976e73e89f4aab4c4959b1540b5a839\",\"6c5df86e3fe889ccbe1817ed06f1e5628819063d46a27d866e361d53570c28af\",\"827886d7ba6b34521d376ee839b720eb9154e0872640bb0d16d0e02751a00df6\",\"b1015852a9b435c83f0d2251ee524f7fc34959e4bc5c451bf266cf1d0bef14e1\",\"982d0b0cd5c5c2d099fcfc42433ed56cac6381fafe75921eaba5e10c348deae0\",\"9b943a5a2d619fe3feb862dc88e229363da7b293cf64615ee63e3ae49d527265\",\"1fc2f8dbf5c5448d26f36b975900d528a7943374b3a8c8834e3a4c1f8b42c84a\",\"23f810fe9c074a18552f9f2eebfbd8fdbce7eaf7e5a6a383eea4970adddcc20d\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1685804},{\"amount\":\"3000000000\",\"public_key\":\"41be1978f58cabf69a9bed5b6cb3c8d588621ef9b67602328da42a213ee42271\",\"index\":1,\"global_index\":7611174,\"rct\":\"86a2c9f1f8e66848cd99bfda7a14d4ac6c3525d06947e21e4e55fe42a368507eb5b234ccdd70beca8b1fc8de4f2ceb1374e0f1fd8810849e7f11316c2cc063060008ffa5ac9827b776993468df21af8c963d12148622354f950cbe1369a92a0c\",\"tx_id\":5334971,\"tx_hash\":\"9d37c7fdeab91abfd1e7e120f5c49eac17b7ac04a97a0c93b51c172115df21ea\",\"tx_pub_key\":\"bd703d7f37995cc7071fb4d2929594b5e2a4c27d2b7c68a9064500ca7bc638b8\",\"tx_prefix_hash\":\"5134ae6e816c62f5b2d0faa09691c698d3975573c4aa54a0f4b2bbe644f803cb\",\"spend_key_images\":[\"3d92d42a105c231997b2fcb13b07ea1526fd4f709daaa8b9157608db387065f9\",\"c7d4d54388c783091330f75ade1e05a0f42cd27a76eea6e79d8216c112a06154\",\"e03fe852259566c7cf990a6b8111bee4cea82acb1efa0de842956c262735ba56\",\"6f3c8c103931717f6ee25528a78c8246650db30b18e50817965d9c1d7dbdfc2c\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1688794},{\"amount\":\"2472530000\",\"public_key\":\"87d176b9e23e4ef65e53a513ebf977e6dfe56e7dc485d594cd9ab03b8deb069f\",\"index\":0,\"global_index\":7620543,\"rct\":\"0d6ebf7d0368dd42e436c75ec15cb8c0139435ec872a69401ee5c3709334d11acb7c0638c6be042f804acbe42bb2cb614e7e8526daabfdb4922112ace2ea980da3f78ec1fdcb6c9d00f8e50fbabc0f413b627826577476f29637f12782933809\",\"tx_id\":5339103,\"tx_hash\":\"93ab2d0be17c12759177fe92f441dd0385474e1045fe4ce1bc4ec44ae8bf68e1\",\"tx_pub_key\":\"80f141605b701122a9d48e787f853d35f79c45255c96061265ea27ebec30c5de\",\"tx_prefix_hash\":\"fd15eebf79d8c415506b92f8d95db58f0d7bb21d161f67dc7caedbae5fa9e9b6\",\"spend_key_images\":[\"8de12219189365412bface90927cb755128ce095b7edf0a9edae3957ba404b1c\",\"ce00d3d65360261d37cc0782b2dc0ddb19183f1e0173c76e7469276bb2d75346\",\"bac11a568f9ab4d5912e866385040a9a019b2e661ef73e2030e2174c45c67ffe\",\"8be64ba90413e21dc9c125da54e840555f735917da34fa1278536760eae1abc8\",\"c4e2b7ba488b44a0b044afdd19c5f629ebe3add0eb12f6f3b3949a2072260c81\",\"b7ac14899b6dce11fed5cb523422132df7bf606f56e8fe24d2d75d12315633a3\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689341},{\"amount\":\"2206678477\",\"public_key\":\"2ba77a7fc821b6b529f8d9ce759de4a00293940c34f64c0d2455955616e027ee\",\"index\":0,\"global_index\":7620931,\"rct\":\"1c09edccc107c6b3a4321368d41659db625f8ef3dfd1fe05094800c28495b7c3d201c08df9e2df65ff1a62ba2f4bb77f6c546121f7614aaa553fa81bc6fef00fbe7dd9bc23801de468cd6833fb2c845ea9bf2bddfa06f9a4a137ccf8add97608\",\"tx_id\":5339254,\"tx_hash\":\"2d649a4245d9bfe050bd4a38e2d396b73cae854e937bab4ff9efcecfff2b03ca\",\"tx_pub_key\":\"97939fce215e31b5a1bc3e08442582edc2d9ff8a6c685acaeb49ef6e5e9983d8\",\"tx_prefix_hash\":\"48ada81cb4a2ab72fc1c71ed5a4ccb4aa5619df68619a2dfdd229bf8542c2584\",\"spend_key_images\":[\"ccf13ff788cfd016816cc1b2d8621011b027aefb824987869cf475412d14ba08\",\"b4496d9e1c4fc5c8c4082dbf4ac2230123e5a2f433f6854550032944762d9d2f\",\"7755a8f8876d3d182b51340f0e099dd96c8d0b9a58bf59b40b81110b6e005751\",\"4fad0faac20edeeee1fef0c83be80a8c9d029c80120d0862a66cc8038abfca89\",\"0de91848d828c13962bc3488cab2e1e363f2bbda9db6ac952f0cacbedbddf52b\",\"f37c350484ecab28298d47612e894a89770d360abf6aaa1c1cb6ece1ef2e90b8\",\"51c82c8fea9542d9c406d7bacc40341376ec2fbf64859efb15525b65d37a173f\",\"642e539376006706af27f89f5ea9d41f18125ff6c6c06935e0caedd38cf3333d\",\"a846b2956047514f6003f9120041a958476d89b2afb3a564c2c56273eed22983\",\"e78bf78a5ef33f5d494badc6d4605162aa4007e9c280e727d3882a24e2637fdf\",\"ad1fa48097f01c5392f028985c58aaf17730a3a436d2f30db71397a571d3dd16\",\"69e05b9b4506e775b1597f55351c93ddd24305744320a0eac42df76df81abf84\",\"7b243c9913453e31ccdc37cebfd4b049cc8a00e70b5384a6561d4aaa2dba7ba3\",\"d843754e944407b2f56e785b77f08901f49892d8bc3a61a3972203db938d9747\",\"abc26133bcce777eb7490dd2267926b9305954b95c35b0dac65d0f53b15f40c0\",\"7138a311847fb52c4c1015415a72a70c98700d8eb0c5cf4eb213da7324518850\",\"871235827e65f0cc08844f7422aa75361fe747bf33ec581126ad01ac1af87cc0\",\"c05bb5f3c13582d078a759ef4dfbbd6ec1501039effb318b08fc520db2b2e82c\",\"729c2a0ea9a39f6b83012a4ccfcba3d94a44eacd89ff16ada8bc4bbb7c92ff39\",\"fc5090d02b92fd825c39b081505130e86c84291c867c822d1cd8188f3c4cbb8b\",\"c8d7c81ab76ffce43f2e1c3d394b03ac099f80a71c78373aa245afa998b56d21\",\"8a673f9887d08db7b362a6593527de7de3757958bd620de8aa15374b371c3368\",\"f986046855a0897983f3744ffadcab90786f4364137ee7b78bcc9674e130cf28\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689361},{\"amount\":\"500000000\",\"public_key\":\"4c1ed19c7f5e05fd84ca1e8c1973e29c612a4945950c068599637921f77da4d2\",\"index\":0,\"global_index\":7620953,\"rct\":\"daa0502ea35a522a1f6542896cc647c50dcdc5c53114df28c02dd85567b049d3c8167944f950e65ec6781663accb51dcf8d5bb78b2d4882c7c9bfa01145f1b018139632950f86e8adf13ab8ecd3973ebdc621f386a040e5001e6f1d70f578605\",\"tx_id\":5339268,\"tx_hash\":\"09872802704f33779a3aaa5ba83414fd87cc0563a5a7b7f2c56101d0c7eec265\",\"tx_pub_key\":\"75cbbe37df2e493a73a287b11486052d08232c77ddd286905afc6b40102fd8a5\",\"tx_prefix_hash\":\"1705608192bb901a70cf1eca0fdeac5a8c3102ad98052f545da43ace5e3a72a8\",\"spend_key_images\":[\"a703430d1b8e573977e9ef76d4073d6fd00e3407024e4fe674dfc9f3c06fe946\",\"2dd3e95c4f12781ceeff09f454c4f833e6f97c2c6caf2fd05473782db7edb60a\",\"c7be2e9f7167fe0d6d6e2ae0da4b1eb19e43838af9f2456bb1fd263c1751d7dd\",\"3e3ce6b82e159c9e0d7cdd442b191b312be4d51c372af8a65ac494dfe88a6355\",\"dfabd690a7d67e8641ad9906ce7b82980d3a060cfa4a1d7f8cd0803509f72ef3\",\"3b3b7eaf4973da3687c58239a8ab5033155fa695ba1b2a1ec60be76e3c78cf2d\",\"00620d5ac90d489e9e7795dd6d21b64c670e1e2628e06531e06446c14dbeeb93\",\"f0b4bd0a4f1d32e5a64ddc97153a3a61780423420339354e5ca5dba39de9edfe\",\"23a885b36ba7856f1575fbd4281bf63b7f2a9a706834e43a15073371bd14ebef\",\"99a97f7e8b941eface1d7e16ccc99850d7e2e13b5852586dd47e27cd2cf56886\",\"d2a4073828a33f39a8175e8a29b406434cb6e044fa2c8470af9e899d2c3922d3\",\"0d4b313c375b475bce7ed84f3b78beaf7c6ed474585a2ec25921625fc0d633ca\",\"027979ce87de96694383bc12d985007e7bc498ec1856806227475a96e76809d4\",\"88fffce88ce059ba28a95b0773ba8eb74254a608ee684dceeb701a6920a295a0\",\"34a2f197fbf1187c7b5357c5666c2a44bf9b774800542b2c6adbc72272781104\",\"4ac958a961fb88032e00b0f25fa59e989ec24274745148b9e8fffd19c072563e\",\"538efbe8e3fb085902a0f3be1da0da3ce8d893d1e08d13c09a5c1261d8e511cf\",\"fb2ffe41c36fc1ee2ba66ecb20790f2387d020b5e50f53776fac2a9a8b2836d6\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689367},{\"amount\":\"2640015187\",\"public_key\":\"75612771957284a42faf99fce05743ba677eb816b33ee249b7c7b78cb8ea7e3a\",\"index\":0,\"global_index\":7621439,\"rct\":\"d58c7fa7381892c240d99ecd0194b859f7ba8ba9eb7915ddb10e49347adbbe9fd93686008462f474a36e65dbde13d5e6c8044d45541299da330abbf5aca4050141e5b03ea14247a2b4edb5178fa229a8a8506479279a5add0d1d0186678a2802\",\"tx_id\":5339474,\"tx_hash\":\"aa6b39555f3838efa161ff160dec4ff2e845f946b14e7be7b34249239f4c864e\",\"tx_pub_key\":\"c83c3515296ef2273f06f2e5f64e7df7e83576acd1f21b8a850ef6e82a9cf9e1\",\"tx_prefix_hash\":\"cdf3df9fd55f1257b645875c1354bd478271189c7e87dadfc40376ea52050d9b\",\"spend_key_images\":[\"527084facb643a7ff5e46d79efc0f6ffd66dcd4626c8ee2072540f2ae32c9fac\",\"2907d9ace699cf874a231b5cce398fbe358713e39846f56a095d5771581e3a7f\",\"f6e87e2e8f01258a9b8a5e25f19d5ff69cebbe20fb1289cc1159424a965fc249\",\"c5943ac45124cdbbb9511d0ec36138716023a830da9200c7c0649d8e922df293\",\"1d3ff1a0094d2714c5d096e023dbf07df0988d0e329638f43d50650ab4331b41\",\"2b73137b85a3f984750ba112a39b5f1e2d0af6119aa35178a5f774927608119d\",\"7dc9238418f4d4c64a82da2168154c9d698d292104ddbc36102de57dc014e51d\",\"c9908910d05360b934c1391d7cfaf72e464f1a9d09348e462dbea8106eb06ca3\",\"337e3ae628323d6819d6ccd9298e0fc45cc9a044bff223b4718805d1d0a748ee\",\"fb047997d6f467a753b55a6188a266f5812da85af68460aaaa639a2077ab9fdb\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689403},{\"amount\":\"100000000\",\"public_key\":\"2a7f99d11c27204de50a4f97138e1b0c174f3fd4a47adc5ad5607467da73cfad\",\"index\":1,\"global_index\":7622246,\"rct\":\"6b53edad90e2f9670e1dc9312fdfaba24521290d30de34d1e9b9fa3fffa063ff4c0bb8682192fb12e8a967908d89c9a16164a8f9f5c8b16a8d9b8a596094180ce27650ed344709c8e96fe077125e83764368a6e6c03d29ac6b528fecf558970e\",\"tx_id\":5339797,\"tx_hash\":\"1e53ad482ff9b08715bd000ea976ad0d8e769af7b0398ae2e427196d71555867\",\"tx_pub_key\":\"dd2e90740eae9087faa59b09561e432ff9da1cc3d512d06cc563570c03d222cf\",\"tx_prefix_hash\":\"7e72d5426c1e3b5f36887a679d6e4159c8eaa36fd466ba336c4999819cfbb6a7\",\"spend_key_images\":[\"b9fc8badf8bbe70e0977ef0f6b38b4a465f68a95d328dce2d90f8a9d8b7e8a0f\",\"23209d4eae3d5585144469a8978cfc401541d8390e190edca2bb7b829e595209\",\"4c569624dce3936b89456889b8bcf9d1a4d7046c7455eea6330d8864edbcbb08\",\"dfd598291433087d8d28c36a33a66b50aa41da0f249789c86e98a0c30ded0fe2\",\"5e33f62a5c53452a7de587204f8f8dd4d5de9d509a2f74c7be604af320e860f6\",\"0579f7312b35abf761633a360f07c00a80edaebea7a399e726caa33cb1cd556d\",\"63e8518c285fb1bf0e73175865964a7dba434155aae60b0934c81a7888ec7b16\",\"9c7a2e1323770c2742c66b1049d11f82313ebc82a885746ae75567282b41208e\",\"5b9330ceb48db4ddf9c2c0f215247fe99ff18220f03e25c091d077091a393dbe\",\"916db4f89364f0dd6952a7966e8f1b89c56218e28843c92e1105802ad49dc2e3\",\"777c424ba1acaecee79cffeefedfcbf9e43b3b7b5d342f299efd728dd7655520\",\"54cf471f8657d3b9b49c4e181ce2f2cd14048e23ede0bdc0cc624a1213f64b3a\",\"ed9866f0797ea5e91911787724bf754c87d90012e89d42b47b57c567590601a0\",\"257e7fc36c242dcccb10fd909209d888520e90992d5b727e7742e96218a1fe9c\",\"97c386e56b9623fe0ff64c4d6aa13939d2ca1911450e9ab4bc717910e1a91d32\",\"b3b5a13c2af9559934e130d6e789d38ac88835c15e74ff4028bea05d0e439dec\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689457},{\"amount\":\"574241297\",\"public_key\":\"ab6438af7ed6533c1e5950b992dbf8fb7be01215e72115756910cfc7e49b1749\",\"index\":0,\"global_index\":7629623,\"rct\":\"62b9354e00b8e088ca89d02732831b68dbd4fd15a308653dfbb585b2a056334f748afb0c4abcea80d099009a9674fa41d46d2d53a9eb5120dca14076ceae1106b0d28bccc85fd61ed4fd9de146721ec738913d4ed56d2b92a9e725fa9b7ae00e\",\"tx_id\":5343007,\"tx_hash\":\"71bbadd152f77289d62414fbcd7b8cc1d0a91cf882c47fe744c47fdac0f77f57\",\"tx_pub_key\":\"07389ba0e8cf80b6a85106c206df6f225ac155b6d90ab33196532f26f24e08be\",\"tx_prefix_hash\":\"afc5d1d8a66ebe428cdffa1b4db526aeec4217389d1c56e610df76cb281ae685\",\"spend_key_images\":[\"e291944be8fe379002defaadf6fcab7e490715f74b8e9d997ad838c1170670da\",\"070f3a89055e82b89a91df6445a43894c08de8394c7730abec35c3965ed416b5\",\"ecdf221e4f7d619e1fc7b550d4cb4c3234104d025f7d5d9990febf1a71f49751\",\"3166a446d35a5c06b308c21e5479a354d439546b73bac7fce7dbe0a8fedf4202\",\"fcf5a8fd0e128164499196886d9e4b13c0a15fb4d6351b82f359c15c32f3ea86\",\"67858ba5134322a3519070b4f1500e44329371b76814c3fa9238917f08d7d099\",\"6f0266c8008e2108fb76564d39c3d9d4127f3fbb58970fd501b71dabe11c56ae\",\"96b07db5c1061dc26dea41478201703002d8240b71c43dbd10eebce8862e91ca\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689952},{\"amount\":\"2000000000\",\"public_key\":\"a9220abbae27b63645768737b8d7bfbddef91800ee96e599391ffa98fd37cf6d\",\"index\":1,\"global_index\":7629624,\"rct\":\"f8f9e91560cc3d761a8c8023ef5c5d68d585ebee5e68d25ec32ea0424cad46b9be08afc900b232959510019901d535cdb21812edddf924afd57e7195b9ef500c64c4422be8ff965c5115955b56b6dd04f9744b1f9475da73da970ffe347b0506\",\"tx_id\":5343007,\"tx_hash\":\"71bbadd152f77289d62414fbcd7b8cc1d0a91cf882c47fe744c47fdac0f77f57\",\"tx_pub_key\":\"07389ba0e8cf80b6a85106c206df6f225ac155b6d90ab33196532f26f24e08be\",\"tx_prefix_hash\":\"afc5d1d8a66ebe428cdffa1b4db526aeec4217389d1c56e610df76cb281ae685\",\"spend_key_images\":[\"f53002c4d3e6318b398df501f5b0dc7285ec2c03245d8b58ddf4c2aae1e81221\",\"76147dae0c519ee78aff1dab662149c3fcda94e6d094bcdba35d43875b382589\",\"d1c34cf67593fd4dd04885708af2c48d65c6d5cae2dab2c0d0b7277ddc402132\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689952},{\"amount\":\"200000000\",\"public_key\":\"e9547bb1c99870b7043f12d2775ae44e10bdf42fcd469721a4666d9ed9ca0623\",\"index\":0,\"global_index\":7629834,\"rct\":\"05bed2f3d0718f18fb6324f228952ad98550092bab4a4e3b52d7fc19695b0e7d32015db1dc6be4938ab0ef1ad262fe07f39a9a6df35a27885e5aac3e6faca60fe27eb278e67bc693912709278f0f7ce2b8d5c8e2d9909d54fe3f7ec710828b04\",\"tx_id\":5343115,\"tx_hash\":\"b44ad5355590f8c43ba34f1e1da853e4518ed01f3fd5d1243cc90a07198df110\",\"tx_pub_key\":\"be92d88db2370c19d6130e3a78a938d0f691bf29c6c45b57a384124df716b950\",\"tx_prefix_hash\":\"79e7a4de85f018481b43c0979cd9eedd74402fc133a913a128d3fb52e7ea20e7\",\"spend_key_images\":[\"8ecba6bc3bf83de48e779367bd9b9dad6a6c2f84974ef26a500607c6fdbd4c7b\",\"27824ac34768690eb58278c91b0eb8ca85f60c32d0a906745925bd7ee14c6c9c\",\"94ab6f227f8170d4e0b545de5e6b616037122991c7190b016f23a3ea2196310d\",\"11475f2b9ca24e435e02393cbe085b3d423baa009fc017daa0d5a6f1a5ab8a5a\",\"a23c38ef46635f0f5734d84e0a38cbee5069836f43d81dfebd6ec54d2c8b56a5\",\"8ce80142593df1cb371e4559e6f92c43bd5391ed64353ab53cd01a8a1ea969fb\",\"b850a26d4ca12c911f73f94eafb3ede4595d696ffe743b086f434616078a6ede\",\"74a7d466a81dc2b1000711a2f09a91a7d61adf4bc90165311a97a7816f9f7077\",\"7b151b1db3b19514dacb01f58adaece2e825794affecdc93775472149de7154e\",\"85f0bc2e850e509474e6377aaec30cc2b882efefe6bdcc65b0e97a36ddb759cd\",\"309fe9bb0eff8103f6a658acbbc29e1832fe45e45f7526f0af29ac5ca606e113\",\"de407047e58f401108b6cd8ae8446469d615dda7656d6956abf1a03db1a49378\",\"cb93d443798cc0186aa865fc8f6a49523908dd0d899779aaba7099a3ca5a63d3\",\"e8e0df02d30db6536711414bc2f84df79e7ae608f2d9766dcb3c97a0f17bc67b\",\"54267d2c6157b9161c4f90aff67267f7a243de86484705a71229f9901b07d60d\",\"8f28ff80ee7d9506b060bb1b628c86b7316892fc3e77bf18d0fcabde20e22791\",\"eda133fc60d40f8b66960aed9cafe67f9fab73533b333ddd18b03d8bce0005dc\",\"308a122e4a705c5df5217b51a6764d937edb1fdf87290bec955ebad2cc7ecf15\",\"d8e7a7dcd956259dd99d3fee4a18cd9e44a61645f0bb60af5690cf2f20b79f02\",\"78e7b87b385f825a7be495c6f9f38985b763bc2b75f6880585577d5022fd75f5\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689966},{\"amount\":\"1734226110\",\"public_key\":\"cda4dfc88d055517f50ebb67f85a2e7d9f14061d1a3bd1a31ab922ceca858410\",\"index\":1,\"global_index\":7629835,\"rct\":\"42055ac87ad2edd086c11cb1816c865693f387dad44dca1e16285632e042aa0d1575322211464443adf82bc3d2084a3ac3401fec0fc63ac82e6b4b6520341b016b4a1d76d4f4b0b449ef3ddd4ed73fd7cc846e233c0ae3805dc3ac9c718fe30b\",\"tx_id\":5343115,\"tx_hash\":\"b44ad5355590f8c43ba34f1e1da853e4518ed01f3fd5d1243cc90a07198df110\",\"tx_pub_key\":\"be92d88db2370c19d6130e3a78a938d0f691bf29c6c45b57a384124df716b950\",\"tx_prefix_hash\":\"79e7a4de85f018481b43c0979cd9eedd74402fc133a913a128d3fb52e7ea20e7\",\"spend_key_images\":[\"eb701bccda793f6b9751d3e0746b605e171ec8887b2eb366a04a545264614623\",\"c1fda28cd78bf3406b7dffe214074e47fa0e4fce490a4dbf0c35494eb34caccf\",\"4edd82900bdada2fa2b0485429db3b90c1a2631faf68a6df61eef2ff21be6aeb\",\"4015eaeb460f5d05501b0a44c7de8eb525bc67994f50b26d6026617658dc5ee5\",\"1101983979eaf3f4c9c1971bc1c4e2665cc0c7e86cb53c913f861d726b7df9d3\",\"603b468f3f5d71b7bcc599810d6d615e411699809e399ea0eb50bcd1cd7c571b\",\"32511641175ec648b7688a669b86fbf59e0fec73b6444adc4605fd55873691d3\",\"8b7da9ff2268851a60193c6ee32bf6557966a415fd18adac8fd0aa6708a53881\",\"22d2c923f0d4fbc182098d97c6e32580dd6326e1a9a03b98c90598adeb248401\",\"c86a3d91213b812218f0835298abce9be71c88d981ba8a9d353394a6277d910b\",\"f981eada4f2762fb7c177f585e1eea70e0a3840460b4cd8ed408bf16d197efa2\",\"f70bd479ea53e810ca8fe78dfaad78c1c94a7eff56f247b1fa02a96f8c59e792\",\"cc49a292e2b34b18b515f932728518442cd76b982e35b8f37d92a22c93fcd4d2\",\"b7a07e904356853feb209aae0f8775c95d8adc6ba6b9b9208ef4038005a567a1\",\"5b28db6ffca4b6eb487ecc9f81279b83af19bc0f15cad16320d5d854d2c5085a\",\"584a8b6cb4d785ac4409a2c9058ec917c96cb2c8b90e27c6c49943fac502a641\",\"d28ea42eed3092110c3df9a288420c21020e1ab7e2897ac73fd718877c79b070\",\"a784dd66b95d799b0f365f96205bb1e4845b0240c6c3f88cbad3fdd6bee86198\",\"7c4b3a8392d246585c696e7f668607bcf61cb077ef83d09d70d408cfd6d7663f\",\"8e4d8434bc7661a4140c34d9e345bd0d3dedcc98223b8da4115adb56edad3b05\",\"a6b3fd22bb08bad78fd5693c2f17c56a65bc21d2ab9af8bc06c474cd022c3674\",\"fcd1a3b4de7cc8edc337669367efce9dccb3343245b49c8fdb0487e5ff09955a\",\"101697f426c628f338180b22bb2d95744d9018a70f66a212ae6c5c58bdb0baa4\",\"68d5e1e18011fadfe938375dd64c3290a4f1a55b3d5c75bed7b8d1d616abef81\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1689966},{\"amount\":\"20000000\",\"public_key\":\"b2e9d772c8813d4b9e8b49640777f5b500a1ce8e1c2f1439360e61f2c882210b\",\"index\":1,\"global_index\":7633502,\"rct\":\"95d2cf2f5842fb9d97e311165f6082e12e8a20f8637211a4c7dcca419a05bf9396cab9d97dc74422203762dcd87acd7e89c3cba720b6ceb2a325c675422086027d0623ed91839a35f24635d0e7414ca6d2087e9743238c1d725fc5bd784bd60d\",\"tx_id\":5344613,\"tx_hash\":\"2f9c6e5a83a3e6b0233718489c1b83f6b2211f8bc6c30847e3eb01552b03007c\",\"tx_pub_key\":\"e607b1cfb89cca764edbc8b00f5fbdc1026e93a68b9f997a3eeaa19e11bb8ba7\",\"tx_prefix_hash\":\"b09b9775de1d2192f9db4cfa4132bc9c050a02273df2438a5a918a44f329c9be\",\"spend_key_images\":[\"50281bec999f4ebcce932223c76f1b86fc573d995f341d637dab3ac8fe6b0543\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1690149},{\"amount\":\"2500660897\",\"public_key\":\"b359f022799b8ded8cd1ebce321bd09cc85adbcf497c6a1db887741bcf9ffd33\",\"index\":1,\"global_index\":7643105,\"rct\":\"bb867d38e736d885ff56835ff1d54e5baeec6d187614d91d7bf21ae6e3e6d7616043b7c9d133c56bee304ffad8e677ddeb5a6a2f20c01dbf3f077caa11c8ec085fdffe042ab622fb845a264413b17de99d8adf240fec85c80ed759caafcd7d0d\",\"tx_id\":5348870,\"tx_hash\":\"0ef6ea6745cd7228e13389600d2c9d923fe14c254852890e6455216127fd9fc1\",\"tx_pub_key\":\"7fd53988422078e8301199791fcef027ee7549a34b76516a3f612b74bd011e42\",\"tx_prefix_hash\":\"cf4011a2bc29a1192ce53c9799a4ab77d8f11d6c53744b8dda0723794d9290de\",\"spend_key_images\":[\"f44741387a8fd17481c8c05c59f3a6ae3702ce8054accd12ecf6c0b3ba5234e1\",\"3ebd66ef7a8f9981c714100c739cc4443484b786030cc5778e563418b3311f67\",\"05da110ef7c04b86f4ba835ed4970015dc04917b49b3ead08e4ca529eda8875e\",\"ea33cb128bfb8bd9cd799351b634469b2b9d1549ce847227087e014af7571bb4\",\"7c6a44ab3ec3513c3db207dccf0138bf83c0d7b2c4b4cec4c3849c0161b7590e\",\"0ad55d7d66124727f0b74b7a45634967141a0826a3539050581f256e15ba1aaa\",\"f3c6fbed3d393d71dede0ade834d0b460ef677d7268af2fe840a5aef4ecb29c9\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1690788},{\"amount\":\"10000000\",\"public_key\":\"3105932278cc4cb300c758187b2127fcf2ebc659f65146d4224a357ea36b4019\",\"index\":0,\"global_index\":7643148,\"rct\":\"479a66e8d1c5f0a187c7dbae24be5d2b075a76d73d9114ed677fdfb0f5866f676a191814ee1b241f754992b3e4728eb7a37b8ddece87aaedd6b8f6c3b874240db83bb4fdca44edc7fcbde7ff3529b4ca66328d0bf6e8a0c41ac2b86ac5696507\",\"tx_id\":5348893,\"tx_hash\":\"01b53f66837c201fceca137f4b0f759b868e7dcfc2359a0d554b5097509c079e\",\"tx_pub_key\":\"4b6c606ef460bec01056c91a0baed3e7c99ce98326d38b2aaa90d25c5b76f56b\",\"tx_prefix_hash\":\"fceecc7ea250697cb2867e52533efef1375e32130c62ae47df43633150b8520f\",\"spend_key_images\":[\"c3c2d5544380361cc1e73ba72f8e901fffc829c9b798e44ad656b4fdfe581215\",\"76147dae0c519ee78aff1dab662149c3fcda94e6d094bcdba35d43875b382589\",\"e426414bd56e6ce60c769ae2a50a9c7a928e2902ba61314587fae3b2b5151004\",\"5574942658bc2c88d414902c424f8ef41162e819b67bd46f72f51a9d7da42e25\",\"0492b196d31ec94d220792d0a26ac81f8b138aa03bf9eb7e591894b63a34b7de\",\"16b9dac28b42b46d9e37fad76fcf6f1381ca47980e38fe7ca11f770dec7dabd5\",\"0c0d370ca9315752305ca9bf1556804dba12b065d0ec55c86ba533000f30484d\",\"a6863ed67d2b823bbfad6d04103eadbd6fa174972b66a638c68a1d8d7f531001\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1690790},{\"amount\":\"2415071720\",\"public_key\":\"f349be5dfb6bb54f46a4a96b9b54e13aeeaa31d2746fd856e45b336211fca089\",\"index\":0,\"global_index\":7654987,\"rct\":\"61219e4f1c67f8fbe300527d5b72130dbfef8b00b30129670f9720164ee293b5fc9dc7f99f7211d89df5176305a75bfb31ea1a5997b35341a5124182ec18b20c8460c13b8acbf1d5d40ffbba8f5b6cb62d5ad854ad37f23fb8ab6bff173be800\",\"tx_id\":5353647,\"tx_hash\":\"adc14ed3a5fc7f0e57034f3ffa0d29f0c2979c4d7aea99ca0472e342f4bd0684\",\"tx_pub_key\":\"2dbccdef1e92f00c0f62dd8fda05da1bc86df8e28f1b2afab2fdafeba45b57e9\",\"tx_prefix_hash\":\"9113023cf63c52c3a9a6d05f7783bf783505a127aea08ab50d01290894082c2a\",\"spend_key_images\":[\"f99cad717c71ad19a20ac1a84e3c4565d730118e772a804a9b7f2c876968cd90\",\"962cfddf271596ab3a9e21a942caa422b8727951b9584a16348c97f27c83e379\",\"dfb02506e77a9b7b70e00f362b314f518bf9d53fbeea5f343b1a3729d34d3f37\",\"662086411d1e690aa2062dad9675a5279d410bfe560ba435fd7957407e7a6dbb\",\"efd825e6dc3dba7a55d7bcf581520552a059f087d269879ec78661303c052d8b\",\"ec84f9392091f1002df609558d163c759e3f6ab3f3e952dcac542eebbf95c2b2\",\"d1af2fc4922c16f0f9e843a65cabf56e2d43f7d5cd88a389f48354053b8e8f3b\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1691483},{\"amount\":\"20000000\",\"public_key\":\"03f1dff3c797d0a32443ef4b325b25e233baa1cd4c91431bea4baf11a005d9e2\",\"index\":1,\"global_index\":7654988,\"rct\":\"6ebcf68cca73259aafe523d35f4e605af4cc9bf8abc1a121486d36b282efc46f0a0c7ce24fb39633e421ffe5ae836ec5ee8bad71f054407decb1912049891c024f24dd09bb80d842735e384e91777f34b7a5ae586fa6108bc1334766e36f5400\",\"tx_id\":5353647,\"tx_hash\":\"adc14ed3a5fc7f0e57034f3ffa0d29f0c2979c4d7aea99ca0472e342f4bd0684\",\"tx_pub_key\":\"2dbccdef1e92f00c0f62dd8fda05da1bc86df8e28f1b2afab2fdafeba45b57e9\",\"tx_prefix_hash\":\"9113023cf63c52c3a9a6d05f7783bf783505a127aea08ab50d01290894082c2a\",\"spend_key_images\":[\"5fed6f81bea9fd4b3cebaddd998d745040925eef2f62ca45042cc6f807935fb4\",\"65aa84917e4d2e1f0b2a703b0f70ad5ec32d577cc22e03a6c8b73db598a3b02b\",\"4fb03053ba7973606d2cea9e562a2fcb0ea1860da8db94bc699a8360fffd0d9d\",\"cf5a17861216d2f7582c3352092606467e19a19527ac48aa7f87e28fd14d98dc\",\"f0c5cd9d20e61ea731df54aa44e2d36853eb8b9d37dc1f6661cdaffb61ad8f0e\",\"6bdb70b470a9fbc976c52d99dc331476cf08f361617468782823ebbd3f46dc99\",\"a3e8c2b849958dd28b3b5ce79c11fc62c71d4067f5e5cf8258d99519108c6202\",\"406ecdb6b5b5633bf8005e0a9e7006bd60007e2f27898f7198f8c19023652f28\",\"fc9ac2e0753b1c6e740539d4f6ec54f735c2df506675015db9310c615dbbf2ed\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1691483},{\"amount\":\"2149482543\",\"public_key\":\"93beee4128f8b08cf2ce37d5ff69efae3f5a4a0060324857ccc6fb3ba0978914\",\"index\":0,\"global_index\":7655763,\"rct\":\"974da389de2e0bce52bc94580ce90bd9ca621b916595dfb1034ef436e3a4ba443421ddad230edb7045d887f1f0ca46b6379afd4a72df3619bd6b8bcd5af009020c6bc32b8e60a8c2acf70e7489780d374e9e181ead1c3b5b90d7dece30e73704\",\"tx_id\":5353912,\"tx_hash\":\"d38d3ce2ea1026434680355fcc4bab49ab4c656c7fd1de5dad5dd99875929e5e\",\"tx_pub_key\":\"b344da97e20cf1e10faa40e3ec3a29f1e6f6cdefd970dfa906b3af19fc51f0e5\",\"tx_prefix_hash\":\"9b520a14bbcd7f1b32224ef95344943cc0995504a249495ece0e6b93c0bb7d2c\",\"spend_key_images\":[\"d203a911ccc548086f786e671690eb9313963c6616ea0d440da0537cc241be35\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1691506},{\"amount\":\"200000000\",\"public_key\":\"ce0980bc2b7cd21642292caa36ecb64ac74c5f7524a58f693cb3328438d1de47\",\"index\":1,\"global_index\":7655764,\"rct\":\"c09eca695f54e7bdab5a9015d20b2055600061ae030b852a5f8db6e4a7abd9fc1234c8777c50b7535338a41ef58dbf89af75f69ae7c90285c7bae11c71acad07f440121f1ba4c04cf607081fa60c6ded75a74fa51c9a35ea194f4454b13d3107\",\"tx_id\":5353912,\"tx_hash\":\"d38d3ce2ea1026434680355fcc4bab49ab4c656c7fd1de5dad5dd99875929e5e\",\"tx_pub_key\":\"b344da97e20cf1e10faa40e3ec3a29f1e6f6cdefd970dfa906b3af19fc51f0e5\",\"tx_prefix_hash\":\"9b520a14bbcd7f1b32224ef95344943cc0995504a249495ece0e6b93c0bb7d2c\",\"spend_key_images\":[\"9b87ca79e339563008a3d7bfa5e3cc2aed8d6566fe9ecf2d9ee7539d16eb3b10\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1691506},{\"amount\":\"10000000\",\"public_key\":\"af4d9e668ba2bbab18ea3e10bfaefaf59318232c8a2afb3bf9c9b38e25f855be\",\"index\":1,\"global_index\":7722490,\"rct\":\"cd747c7d1dfc4f845fae03f8ad35582a8f3fdb7c1b211a142fca13142bd260d358da0da0a88ca46413546c582ab6a9815a6736cd79c29dc6272f6050f5cf9b00b05137d058fdeffe1957607c6ca3fda3f00da7a6121c417b72ed64a537663b0a\",\"tx_id\":5380811,\"tx_hash\":\"fa008a5e6a9e6eb724e20eae3bc8062fc39fd400feb78bcac92197be84afcaba\",\"tx_pub_key\":\"178557570bfa458222c62bf52f81c1c345c33ad886addfe3d9daaab02e58f83b\",\"tx_prefix_hash\":\"38c2a4d8c847f3afc2053b68faf7fbc620cba3ef08351c0f6f10b6d957975e24\",\"spend_key_images\":[\"cb17b4f17b0651071f96eeedcbdf94bb23b45fe5e21a41c2af900e01c2916a2b\",\"9028036cb7193b434d4421b086fc7c944747ba5f9dbb73b975ef92c94003a805\",\"cf8b62f31fe4d9735932994a1b5df34e5e872cb1d41937a787698020013301c7\",\"8dc640089551bd18ac8ff90a0e7fd0969e4c9a6cd1057bfeae64f884a1747778\",\"7c000d408f2f58454db5b73b13f31d175d37700c53616428c97d8e315e834aea\",\"4ae0e229d67b44d2ad3555cfcd5e16c388941405f83edd706b25ed0c39a86599\",\"79608bb479d58bda2c63a68575186736252217c2b0dd45a723fb982a5755857c\",\"30eaf0e26ff6e61e7025cde8a5c10c41d00392ec988c3e961eeff06fee2d79d1\",\"f5c2ea5643483dfe5a8cb689aed59c084ff677135e98fe2b9aecd8f1b31735d9\",\"a0d047c4268b78fea2b12d46d73e0ca53e3b6cd9631ee5dfe2bc9b327d1eb341\",\"35338f20bd7b6be44a59d6de072df9000640618841c4e787c476b78ba12f4dd0\",\"83cffc0f83c7c5806d1743b0d52e792ac539f71106d3da118e6939ae13f285ee\",\"84c79ef077e0950581380c49797597d7a66118b34a17756d5d3d61a0e76b6be4\",\"7f7c5594351edefd76f7ebe0f52b769f6186cf3d23d9331d0fbc69db7a138173\",\"be35fd5c678967e83c78e52f13abc45f6dfb5a08d36ad88fa09b448c8d01d20d\",\"b7f4b1bb588d2524cc8d4e3c8ba03fd58844a1e12b124b4078e444a487469df5\",\"ae6ce7b1b62ae8132a94a69e31c278c6fc5fb8d3cff564c263f03b39dcf6d7aa\",\"f4c76b08a87eff7ef868288e701a86324de0c4d4a8cdd7017fcb74ecdf8ff2f1\",\"9fef6074480d1989c313b2b790031b041255bbf339b6eac8fe9489a839bef7de\",\"e7ab26ec42798a4b5c2f511c1b01e85486299f94fb0551cdb1b1e1baaff6e1b9\",\"97d4a5fdeb863f47d0e02f8dfcbb8ba96c1ea7c5304835bb7df0c2647798f664\",\"835e04e761499e63ab7e8661d0e3710b4db51e655590229d5fc2d16e934c68ad\",\"ec61ef30f1489d10170032ad94b38aa18ebafe5682a4e7f65798df89ee1add89\",\"c667f88441da138bfa72fb5ecc093b81ba82c84238be9407bbb5897703df0639\",\"686f5e9fc4ae97a6e0e257392afbe0aea4e904381954829a0654806d04215b55\",\"a44b94da87bf66ccd55b15ebd432119e9dac628bbdca27bb5e1c18ebe08bbfe7\",\"74371a1e6ff8bf7c174621d6310ac18860473cb78041cacef8de0e6851eb4961\",\"ca5fbd360aa621f2b4d945926ea55a37f2103449e8882ffc388e68fa7338f7fc\",\"bb040f1089867c1a99af421e625d6bb958798b28e46117c5352ce50798127b2a\",\"702624b859f59aa64eedfc7d8f30e073670d147226d2d37d7989ff40bbb811f4\",\"366e6014f90807a2821712da2ae3ada3887433e8457ad3462f3246b30239764b\",\"178045bdfe6ccbf43b092e020a5177bf92d0d87a03766a9cf18cc14eb4274aa6\",\"96dba11161f270ffa99822a7a5c616c1c2422351625aec361b07fbc2cfee4e69\",\"dacf363be8521071af79cf6543e590eef7dabe49fc45cf03b62ce488b0540d09\",\"c6f2dd83ed5a20a07819d6ab5d178d767359524002767bd21082deb496e3fba9\",\"dacfc926fbf21d05d63caa9226a45b8c997221f0293592176d976ef8bad92aee\",\"4852e27f2266673507c3787fae1fd032458a534dcf24dc5266ea80703f1d1397\",\"4b0c26cd7ff3178146e86566c9bd101bd84a05006fa46a64821fe67859f9c811\",\"ad6857533d4ee80a4c721fb67673e59d35510666cedbbd0c0cad4f78d831e316\",\"14f472c76ddf25c51f5a361c863c3fefdb7f0e521d38fbc6d2801a1ee19e4e33\",\"f3e3f25d074474577accf5bf189fb981b60ca853e86ca1344ce6e81fb823355e\",\"dc868932ac224ebb7b87d32475367a553eda9b36b5905d0fcb0557252a8dad20\",\"8c246de732e32cae4ee7ca514b1fe2acd3a1934782804f8f8eddd00e2b993596\",\"988eba6138d95805add54d5f1de0f178eee377d99cd1a0aa1288819b3f9cdd20\",\"989d54ad65694f2475be9ee5f7df53f52cb25af80e16a164e1e325950c8394c2\",\"146eb196ae486ea5d363f1264183bf46cb2a9f7ea71ae7465c4aabb4900d95d5\",\"84e82b69e8a300e56d20f38790e6b15a87a55a806017441c3d964d1ab0bb52fc\",\"ad9240572704a64fefe9f981f6feb7b05e40ac350b6f12b8ffd09d9e1d39cd92\",\"d36bf805bc4f277fe706f828752fa87726aedee33d4ac894171247f4dde51a0e\",\"b912672dbf1149d475d429c02417eec3837fb36fbdee81be4c326eff979f713a\",\"0a8811cf58cf6ca34714264efa94a7b07e39aa838e24f7b61059585dd43dbc21\",\"fb8d48ac538f08528422601d6477c6e8e0270ff50f116cf5f2b04c5a7be4e269\",\"cd847538e05ca21417694c743748c85c541fcdea06b45008e2808a462ef26c18\",\"4ff839f71b69729c30de459da086f48b73e8162b86b0ff8529e892e458ff738e\",\"6b331951656966429afd43e6f840ca3fbc7948a8f7dddfbcef62cd51f978bb80\",\"eb8dbbfba058fe8ac1a0dd53234d2fe19e740d6ce27810ef2498e6ac55acad72\",\"f84667062cf39955823129517cf87f4163657c57369a970227d8f24bd4fca859\",\"bf733aa9dc15948e7452681265c177c09e1fc503c7c125c1d80275ca0286212b\",\"9dd91121e377313b01ab7db3b2880e20eaeec8c2b3dc52bfd70c2caacded164c\",\"1f623cbab82baf795213d6791cfffb84c0a0e8bb8608f3a25e475dfb6f3b844a\",\"03cee80157fe45c3fb639f4579219de765e0a8c9dcb3a6ad3654de0c07a1b285\",\"5c7b94621f11553059d8f175b8afacaa6b7983fa0c1dcc12932d243baf825721\",\"586781c49788fbd9ebb07be8f6af03b2171346d02e8c03f39c8e15bafc2f03f1\",\"f6d0df6200f18a99108e12a7d6dc4027574a079d426b25b1b2fa9d31390711a4\",\"9b5005f4b41b2582c61f1d4554b6a62605689a81596cf0d751fb3ac9b73b160e\",\"48ffadacd8e3323490a58acc07f91fa9e7baa84357cdac35814468c5b2cf96ce\",\"45bebc20342a375657eb5982f77630bdeed5225494db92db5f71d155e84d649b\",\"b2497e8f4fb8d3e5975f857a794c896c09bf939744560275353f0133369f62eb\",\"cc696b003605f692b523a124c0d62372fc88814799e5da64ddacd882d3cbbeff\",\"4a9f0b31b2acbe9f86e953e9ae141fb3129ca9111b90e908c8cad23ac02fa10a\",\"9194c9a3c4b30f28ced8f9b4fc87be7d999a15973d93bedb3a1f881ac86aa560\",\"1d9ef4dad6843c2b5614b0410a147c1072c6bc46e7aa07d10db6372128dc5da7\",\"48ed8c1b29d0998ee06215afb5bc43e022f4a13cafd474c9f51d0045683cc9a1\",\"ac9adcee6cd6c68848910c9379d40e5d011cb581731b011348c8fae962e20e52\",\"170cecbdd913748f17ff75dfd8794d046d5d5b29fb50e1a9e0709de8ba865ee3\",\"105ec0f200ae869603c67dafb25bd9c771e76f6811ca5ffc64dfb3433d572fdd\",\"68a3c223fc1b8be4917212b7325c40155bce25dedc206b08d5c422a23e585aa3\",\"5ed50888684915624b26c5775816016246af28e47fda63585dd4acfd8336b644\",\"b4ce1182f818dd298ce18cc21485dafcd7ebd30160e1cc7002460795715baa6c\",\"faa05164cd5548c547b3cf6aca3fb531edd48518f5172212252a1d622ad0b9fd\",\"0bff493967cc265475f46aca4be5cf8503a3d44ac6293ad3dd49e62f9aae6df5\",\"838265b15065c9c4fcf7607b349bd37f371a95ad94c46704ed0edbb1ae356f57\",\"54b7e1225b89a118efaa464745595a59110f091ec9923a58609cbb31e822e416\",\"cbcd1f936c141b01ec716ad3ff49ef2a2669563bae67a0a7ae1949111e4f0274\",\"df37ac60c19935fe940b120c7d7291d55608c1d2290fa51b0b3cd8a773db2e8b\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1695070},{\"amount\":\"200000\",\"public_key\":\"8415b08b68f34820d44c90f8a176f61e7c7f3db04a15e759f9f447dbfc49ab12\",\"index\":0,\"global_index\":7731469,\"rct\":\"2e6644a541ce3b099ae2345889fe97f8f92063c533cd1eb98a1f7fd4e00435be58cae0b1c49f63ae4253a6b40b233ef208b4a5dde9be907dd5624dc91e2da708d5fe9814f884c8b95c9fe422da007ecdfba2350f48140fe1ebc6b40272ba1504\",\"tx_id\":5384827,\"tx_hash\":\"afd0edfa845e395581d4f5ca79e33a41f6f56e5e3dad2b942cf31453388fab94\",\"tx_pub_key\":\"f54b98f42a3eb9e4d0ece243c445dd2c044ffd212d4a7b3572c5f7aeb0ccabd3\",\"tx_prefix_hash\":\"bf169f64cddfd8b41db3bab5b61c679dc7b6a0f16922a07df1de8d36336559ab\",\"spend_key_images\":[\"012e12631978fe82550817bbb311638f069a62ce9335d42a0e5fa49ca1c0f3dc\",\"15a9a6980ecdbdf5c0d809f7c18eadcb1124a1aaff02d1ef3c4ad74ccb0397ed\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1695679},{\"amount\":\"2044415381\",\"public_key\":\"b1750d31802e602ebb76418af2ebcaa21c1a4e3cceca22c4e1a982170bdd72f2\",\"index\":0,\"global_index\":7731732,\"rct\":\"4d122e19c1b72666aa4bdb45eacf709707489524f296ce2acb29626ad30d456f62ecbc736491f6a58edba4499895c454d7e4bfe9ac56279f5fb7b09b816ac30738babe8d7aef12d9513f65eee24abbb8b13630fee2e31df01d2d570cfa31e600\",\"tx_id\":5384910,\"tx_hash\":\"f156c015bb34e67e67a8b4ee644e5cf337ab8fd91bca38b5f98a43ec3e56273b\",\"tx_pub_key\":\"950dafb87e0d46ec8414967ba910aa9d8fa3f3ab728d387f37446419164455c5\",\"tx_prefix_hash\":\"b6ab5f1b65a7ecaa01ccdac2422fe07ec3fff13cb0a82a811482437f1ebc80cc\",\"spend_key_images\":[\"0ea766344545b5bb9538809820d40b8d410c633ac67b39895a5a3c238a9da0e4\",\"3067f0e229293aaee3295fe3c623968c3d890dea0b50da9fb7d411e4ee8e7ef1\",\"466ad3386347af25ebe967f0c40a56a1c32559ba555e03eb397d1a6fc14ec3f7\",\"f617ba64bea5ccd6f8d1ea9733e9bb1132dbe2f0472bede432ec31a2fc51a243\",\"cb3ba3078863ec64212594cfc5c25d15756dd6c6b352142ffd8abd45bede7b82\",\"b7d7db91b56eaf610c81b9ca23e734652e183ee6567facead82426420f794440\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1695688},{\"amount\":\"40000000\",\"public_key\":\"dd820506d49d3b0def91560ece31abea6808c7c3532ec1f60eeeae31ad65b974\",\"index\":1,\"global_index\":7731733,\"rct\":\"d5badde960c7b1a22867dde84986097e9606c877530aa5132624c8d50a2b50ac59ca0b1cc247766e33d710804e4b4ec1173e1bbc6638d0e2994adc6bb71daa044958ce15ed914da6df15a5a71fb25f316243bbfb13f66c86c65aa17fec2ef707\",\"tx_id\":5384910,\"tx_hash\":\"f156c015bb34e67e67a8b4ee644e5cf337ab8fd91bca38b5f98a43ec3e56273b\",\"tx_pub_key\":\"950dafb87e0d46ec8414967ba910aa9d8fa3f3ab728d387f37446419164455c5\",\"tx_prefix_hash\":\"b6ab5f1b65a7ecaa01ccdac2422fe07ec3fff13cb0a82a811482437f1ebc80cc\",\"spend_key_images\":[\"5489a1ec242c981b44cc57e7123c40e226a5eb1f35ae6ebeee03f73ebff89010\",\"62711747b8f0f398956702f58d3efdff2df4abcca437501f8b2bd7d733d82d88\",\"b68283d3f7d9fc791dc6155a167e8ab2cbc3a18c68b790ca0bae062241f36e06\",\"b0bda53f16244cf8a9076efc07c8c7086a8bad1be578f5e2ec0efced733999b3\",\"439c8ea0c7d797ee0f2fa05a343deb0c614c7daa8676b664b7721187bcb067c0\",\"9071b287b20b381bc400f1767d302ec4aedc613d1fe54a46cba23a5096fad0a9\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1695688},{\"amount\":\"10000\",\"public_key\":\"e6bd8fa0fe055babebf1654ea949ea2ff3363d9c613aa3ccff4bfe52f569faf4\",\"index\":1,\"global_index\":7731852,\"rct\":\"2b285c70e2ebb7e35ec438cd7665939feb520c7c7e78bee7ee9fcda1933a7055aa9ef016c0a5f4527ad178ff654f9813a78fae127d3c06632c19d17b7562cc0bea8cdfa83e5c568713de77b016aef94f74168d9f94dd55e4def00120bc3e9f0b\",\"tx_id\":5384966,\"tx_hash\":\"952885bd22e1073ff78ebc182ec9d779592a7a5ed9e15ccaafdc82b9de27671a\",\"tx_pub_key\":\"a828a96ef306f10f8f39ebb43ab1153e7d19aaf8dce23cdf19e0c3a1b2c688e6\",\"tx_prefix_hash\":\"2d8895eebe7fb9031f577f8c8da8270c586256ca1d1c3b6f3fda3720189663b4\",\"spend_key_images\":[\"7a4ec6d6daf4fc1ec1543e2e20e08dbde62ebeab5b89518139b286ecc89d969f\",\"aa124878709da94bbb314fc8b5610d407b8f219e9309fe986e7d34b80e4c4334\",\"15ea6ee78cc73e5739e92d7ce54f7859c6319c155daf7bae1140d36283f67aa5\",\"1e94fa772aed5c29667eb3da01f3fb76f13fcd712ab42716d4cf9d1a95ee757c\",\"38b88733b6d3cfb0999cfcdf14eefc73c0237ad5aa1b3fd870a566a089d5dff1\",\"ff8ca30bbaf1c44f9d0779571c6039d678248894c8f5427b293674f71de7543f\",\"851c81fd8a0b32a2f79e847d31aeb3c1587f859692465a61d8da2899ffbe4e90\",\"694c2824d50064c463009a4275c8c7527c0a330b0739cd99836553f5557521c6\",\"df3c85c4a775fb9523f7cc4a8064b4b33432d52c529df561aeb8f8cc55c3ad5a\",\"3934ab5828fdbbada04bfb5a8fdf27089fcaa7e29e8708c37a7eafcbcc9e129e\",\"e5808c497ff80cfb9ebf512a9f9f43d51d20367eef6e7d89bff4003c68c00b7d\",\"64bad41c40fc7297d3aeb10ddf3558827b957388baf1752f9018ad8bed74783f\",\"e4f23714ae3da37b4c67ac33a3c073cd183cc2c07126fe8f2e369ce8efb11756\",\"39f5feeefff984252fe873892b4a0116f52e607e5904cd884540d99be5ff62e4\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1695694},{\"amount\":\"10000000\",\"public_key\":\"287107e61d9742453e0981943d94b30911ca9d9f292c0a4b4f9da838b1eb86a9\",\"index\":0,\"global_index\":7801212,\"rct\":\"cbbb8d5944b054757730fabe9a9258dbb121099a5274a48597a9776a4371f660c759955eb20554e94af2c626d49772462eefc5766c12704acb85d8685e3d1b086d561faee25493d4d7a964621c4ca2b4e02c809b61b680becf2b89c82044b605\",\"tx_id\":5415216,\"tx_hash\":\"fad2ab32e7a8153425d32fb3fe3265526573d0575b51231af8efb3c6ba2ca994\",\"tx_pub_key\":\"c27f24a7b26f3978c3453b475a1afc30c78561fde6ed30de92ce11c572e0b7d1\",\"tx_prefix_hash\":\"0ee929e90c7a2503ddd54b414b94b6bde04391c1d318a7d99f7dec7e8478dd6d\",\"spend_key_images\":[\"2d8ea2dbc732f559e012d3ef3ba43b9650c2f5821526d2c90ca7934e273f10b4\",\"48ca7b30c5b70713569a814fdb514bbbeb996b1ba51f79e35e765d03ee3cadcc\",\"6c2dede0185ae16ce3900c2b334d7f185cba9b700289306bb3aa528908ec4190\",\"ecabad5348d3a4f46b3e9d8549060c372b78c1ccb2affebcc66e74e9c1bb4278\",\"c7f56159edcbe9f02b6fc7e8bafc5fd61c6703f4a339878e9786b4f0d9f3dc83\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1700021},{\"amount\":\"1780028177\",\"public_key\":\"42534014ab213cfd6aa1b144d0a1873d269fbc318f7357a0871e2218e4a4dc12\",\"index\":1,\"global_index\":7818929,\"rct\":\"63a1ea2b4cf35720f560a27ef411f83fb8d49d6c5cbeb2e93e0ddbf996e10dc0b0fd91dcbd7545f2edaa15742a93c2b9faf6fa21c1573b1b01d10f363683b50d93c8a1c63a95c3686965bdc3193898cb9b089e994ad16ea2542106391ca84103\",\"tx_id\":5422900,\"tx_hash\":\"d6244d3585ec133bb090e24fbadc7fa26ca3c0b6479a2e0bfc995a0109052f01\",\"tx_pub_key\":\"4cdfab7426b58a36da8bc72998f37561ba63b6feed8ecc781a69a604cb5c1499\",\"tx_prefix_hash\":\"59c1393553fd3539fafc62f7c8d0b86e1c1d5d3c1d28c3067a236366fb448d07\",\"spend_key_images\":[\"c413ab7e1249ea24a3cd577ced519863743fa9ed8ff3a7594a62790bbae8da99\",\"3cefa5a3cf2cd33e40eb589a0689b0e442514f2e52ae96ef745831a6c6ad79d7\",\"4e8060923ed2aa3a2a38028acb2c9dff9312ea9b55bf4165f2763b50f8a0b4fd\",\"9f964a61fb746dfcda54f07aa90a5cda6947645dc3807ae41e3bc4d98015be52\"],\"timestamp\":\"2018-11-14T19:31:53Z\",\"height\":1701083}]}";

string _send_routine__sweep_getRandomOuts_dummyReplyJSONStr = "{\"amount_outs\":[{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6478600\",\"public_key\":\"1a51a97c32b92ee16bcbdefcd572f36610cd76823a44528a96ff0d024e2a6b6d\",\"rct\":\"3c3a83bedf703b50da3ea1f001a794a03e36199c8289e80dbf4834c0b32d8bd5\"},{\"global_index\":\"7387285\",\"public_key\":\"6fdaa719986cf4b1f0c0ab057796c8d292c51e2c6f4fa988a8f85517b3d0d3df\",\"rct\":\"52a20ff6e02c18c10a7b91de3ce94f36de3287e4e77400fc140032184ff30dfe\"},{\"global_index\":\"7680334\",\"public_key\":\"c8de7e6b67ab6e4033590ab423382b9d9c290b3be037360637b3c050a75e9280\",\"rct\":\"83ed23ab140d68a712782ee39494d7f691d6afe44782e818af7292bdb51f4db8\"},{\"global_index\":\"7722664\",\"public_key\":\"8f7e355241f03105faf475f3070b11ef1b0cdecabf165c39a92564c32d09756f\",\"rct\":\"f43c2a397de781d18a9b0b242265263cb2ed26fb40cc9fac1228e2434ddc866f\"},{\"global_index\":\"7829810\",\"public_key\":\"ffffb90a2fa4a30eab0dc89d0fe7fbdbe95055b49001fc163756dca8982163d0\",\"rct\":\"ef12dd0adc8aa6051c18f9846900bb279f8c9e9b97930a8aae37911e30a7aedd\"},{\"global_index\":\"7861666\",\"public_key\":\"bf243c7511088ca6065b71bbe47c69056e1517b159d659c5b82f0c7f841259a4\",\"rct\":\"b8a348ed838b7bf556827745b7ef71c7fef2cbe4c2b83c67f5eb903e081c23c3\"},{\"global_index\":\"7866897\",\"public_key\":\"18df6f38df05eb1cae8119073fdcc3cc09fc79b3ec4baaa3bb3cc63d93e76d82\",\"rct\":\"927d87944cfb827033c685d05d907c4455f662d64efd397566799f7aa8006cb9\"},{\"global_index\":\"7867193\",\"public_key\":\"d1ad81ab293058a548f5b168e5ddadb1447c7b7914031053149eb53973be3620\",\"rct\":\"0160dd071e3859deefa289d27e996e356169f90985d75006741b6a36c71c38da\"},{\"global_index\":\"7876522\",\"public_key\":\"f46ee44b2ef816e7427a9bce0964b07592c86e23429a1c20602e64bcf0139bae\",\"rct\":\"8b1ffcdd2e86e5207672233a9cb30d2b8729fac1cb9f326023ffa65db4e09bdf\"},{\"global_index\":\"7885794\",\"public_key\":\"bc6e9dfe5354fbee384fdb11e23b3a244228027b85af52eac4362438bcd20e23\",\"rct\":\"f59c663f7d415dfbf6459ae7337c29b9f81ae1f7ffdf3b4f452611ea9b838d8c\"},{\"global_index\":\"7826288\",\"public_key\":\"bcdf302f813eb0d1f10046538e6d226344197a12f1f2b54e2f095ca234799818\",\"rct\":\"76d3bc9e1147252be5a4bd45f4552427e93ead62b69be93f1bfb73645d4b94fb\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"7572314\",\"public_key\":\"0477758ef7a78fb0c99cbb2a0f9faa4c85e1ee8b99cd9ffb102a539e570b3b44\",\"rct\":\"34e6aaa6f3aeb45df8dc74e626cc0845e3db6f5f9bd59506cc1fee7e7dddffbe\"},{\"global_index\":\"7772070\",\"public_key\":\"e74d40544df0746c613a854f6401b544999ce4242eb1718b5e1ab7ca3ecda08d\",\"rct\":\"a827403583c7283c05cb3db3ec2930ed14684afa4b5b906b63a71d19e2cc2ad2\"},{\"global_index\":\"7783300\",\"public_key\":\"c2416f761ce191530bc84253fea43cf83e3fb7d03cfd5befdcf84aeed8cde2bd\",\"rct\":\"2498a64a44d6b1dd6ae87e66bb9cf51e9a46f93a964c9645e7316cf5ded3761e\"},{\"global_index\":\"7835881\",\"public_key\":\"3878b4d45c1fdb9afc8d177e427fad6b6609cc1382efeec9138e4e759baee6a4\",\"rct\":\"2ea2bab06178288253ec4d46f3d16d419d7f9cbfa2d4d8b7586a2e044c14f87d\"},{\"global_index\":\"7845569\",\"public_key\":\"bf78585e53b21925dfff9462e0928479f3892cd98b991f5973a85ddff1b63267\",\"rct\":\"dc539fbee461867eada54ee4c46becdc505e4f79a0c9c2d5e6587ca9e8bd10da\"},{\"global_index\":\"7877601\",\"public_key\":\"939b7fca3c60bd00e63328daffc51bfc6f9d85cb402c9e740a7773a84f98957d\",\"rct\":\"a2f921124806ac9204a1a06afbaedcb305a26b01027ab381292ffe4074c40022\"},{\"global_index\":\"7883058\",\"public_key\":\"977f6e676a84a91d5120a534ec531ed22b1d60725da8d5a32628aa753b0eebb7\",\"rct\":\"fbf474120aac8003388b2af9706ae2502a1fee6b1bd692776b5b9d1aa2b3a977\"},{\"global_index\":\"7884736\",\"public_key\":\"3fe000a8d5b63150c38f0ebf9995848a3f7e86470efeb9eee0e89817b2d90f7c\",\"rct\":\"d0d85fc88b015dfb2c056d36a43bb7a6858c9b67a1062096964e5e935aa2854f\"},{\"global_index\":\"7885562\",\"public_key\":\"d361e28435b72229dd3d532c60df465a84a478d495226915ed959d12e75f6fa2\",\"rct\":\"b55ad4ed092a446da60ddb2edd6ab287a05cc329b580c7c99ec46327378dbe86\"},{\"global_index\":\"7886354\",\"public_key\":\"918ff14531d53b667b361ff1a5a04f6cc5eaa90f4053cbef99e060841516cbbd\",\"rct\":\"f3b7251a54f186d43c563df7a0fb4b47a15d5ed49ed1f869efe09bf295dfd030\"},{\"global_index\":\"7531500\",\"public_key\":\"85ffad7f0cd7ab3eb0ee32a7395342ce5341ba7bc0f42566af4a3b915029647f\",\"rct\":\"a8bd4bae14ffbb80ac3f4eecc3133113a157f743be565dafc10b039311ec5308\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6299870\",\"public_key\":\"54d1e570862eaeb679fd074fac3d6138142f58789a154157e4d4e0c469d06101\",\"rct\":\"36ee67eb5ea0ff77d471fe935f45893cb78639cf96e3a47cc6775801e74e8138\"},{\"global_index\":\"7460235\",\"public_key\":\"94a916c73a75b21e0646b898f962605e8ab5ed15b8a894f252266054c638023e\",\"rct\":\"ce280cdf4265a1fd0863c2abab102e93393639936b01e106ba71abf8f221dd64\"},{\"global_index\":\"7873094\",\"public_key\":\"faa3ace51469617859c9429578568c5b960643cee327dbed0cdd0e11806d9b71\",\"rct\":\"b99acf9b016cd9bc67fe2980f3ecf70de97462d59c16f4a09a6383f163780c89\"},{\"global_index\":\"7877259\",\"public_key\":\"cf5b2941138564689df2dd929fe19117449595b8561164e006e2281408dacce7\",\"rct\":\"eaf6dedbe10a47284ccae090ef72acc4403b2296aa234f5671215245d45a2ad8\"},{\"global_index\":\"7878382\",\"public_key\":\"d811498e7fcde521d2960c4bc66b131b06fe80b40c1cf8a446e8ec708b4e588a\",\"rct\":\"150838d9c177004ef606f751d54ce82f64d5b8e977bd163fb7e83bf62795cf25\"},{\"global_index\":\"7884103\",\"public_key\":\"1bf418e610ce68a6dc7949276e45d0d84696fb60a3e654815445c7d289ef33fe\",\"rct\":\"58eccf30ece6c7791dd84e1af61922105cab589a89f5cb90ca60da5ce368f9ce\"},{\"global_index\":\"7884700\",\"public_key\":\"c4faa667be82d656c30ad028abe0c7aeb160a7bae624241ff66262ca3e1806af\",\"rct\":\"04a5d215fd28bfcee1e752b475ec947d24bce3599c3c957ee9c449d73fd3acdd\"},{\"global_index\":\"7885171\",\"public_key\":\"e08fcd78595857a8ec46ef1be4cd3a68c4af347b1fc8e3ee48c584d76a688149\",\"rct\":\"5db9fb16a652cf1cd6e255c8b42d1b471d030b67c67361472dc536aa8efb00ee\"},{\"global_index\":\"7885849\",\"public_key\":\"4a405489c3f200f69f2ba2c637bfe190f7f8c31330b4b92192aa567e53243267\",\"rct\":\"5549c2e2ec3863edf025db97bd9f5385f45a62637d2518f3520bdd3b26e44422\"},{\"global_index\":\"7705652\",\"public_key\":\"311fb134a837ea6a36741545faec0d58290c24465e9c589a4ff51df27c7ed1c2\",\"rct\":\"9adbfad9a97ca66c22d115524cfe5cd0656418709f5ec9142315cbcb336e7e0a\"},{\"global_index\":\"7857899\",\"public_key\":\"d40334871bce369e52df7bbcbe6f82a04ef01d3d9b49cb522d7e85c08296af22\",\"rct\":\"ee5ca6727718632a272a8db6e6a7a6c0487e87a77a2a41d6b0da2395e569634f\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"7419292\",\"public_key\":\"b1366221a0167e740537262103a84d4030983997c239c9da0bafb2c160673f68\",\"rct\":\"205001cc7229b13408c25fde7c2ff0ec4552e0100896232d0d64d9813c001987\"},{\"global_index\":\"7614515\",\"public_key\":\"3341fe7151d5e1d6ae9be5f0dd0c335af01cf70924d6a2269e14d554b18aa370\",\"rct\":\"b7fc481cdb053c081eaeb1443dc82aaa16e41940fa5f78ba75e202f0fabcd795\"},{\"global_index\":\"7742847\",\"public_key\":\"0709c4336afeaa2fcb986f5bdb4346bbb1fa82bb41fcfc34a557d35f86f7948f\",\"rct\":\"8f19251a349c880223303831eb78a26e472c3f2afd259937ec971797835b4e05\"},{\"global_index\":\"7751128\",\"public_key\":\"8496f686f6fbd311d1c233e49c8f51436fbbfb202398c70343b28e978952e192\",\"rct\":\"cdc754361afcac1760273ea2ad8b765c7e8aa2bc282de59f601fb4b70502526c\"},{\"global_index\":\"7787401\",\"public_key\":\"d28c3401593a4f56b72528e16e87e99d52aa3fa471dcee916583f4a597a90ffb\",\"rct\":\"709a89bab5ac13292f7fb8e999716d8e4f9649678cdcc8e785bf607fa2b01144\"},{\"global_index\":\"7823723\",\"public_key\":\"c88352fd8b8128f34410d14f0a6ccf88c003b29a9415dcccafdb1db4d0338cb2\",\"rct\":\"e88eafaa190914c46da26cbcb4adc88697eb8480cf5438dc389486798bf3cc90\"},{\"global_index\":\"7844022\",\"public_key\":\"68fa3530291c6f2ac4d8e742ddb96a2293086d544e90c7f3c699ba1eee3afe7c\",\"rct\":\"d28069d5db36f7e7ec6aa2b5985ae199404e730850f4752423480cc6a706b60c\"},{\"global_index\":\"7852091\",\"public_key\":\"7e3497efbad4a741c6e754ced24dd109cab8b07eab64336ef7747061eec0be1f\",\"rct\":\"40d9dd80163b99a7298a6b6df74b4b3c4259d2a519b94224b39d8a2083f03b4a\"},{\"global_index\":\"7871623\",\"public_key\":\"962c29bc1d8d004440a8b4a63386beb6020ea77369fe22fe8cbcdc3c3724dfdc\",\"rct\":\"abe32f10869624dbe387e6e514f9b7a60364266a15a709d0a0d0a7deaa24eb8d\"},{\"global_index\":\"7882556\",\"public_key\":\"43aec8d5ece63a3231136a8ae6ed6f6badb6ebd01187ed5e24118c4b615aa064\",\"rct\":\"88a997a1f34a7323aa002507522a6c29a038720671bd619c4bec14b391af3776\"},{\"global_index\":\"7868456\",\"public_key\":\"a8b15e6d7178b55d66649e26588aae4c5bf4b0ffce841dedbbe00744287b2a48\",\"rct\":\"577ed69696ee17a51171d9bb15cabccd0c39b4ed2dba621b2fbdf3c9db5e9506\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"7613916\",\"public_key\":\"0376347155dc44d0026f8e9a20b9fc59335404a0b351c230e484a4aff8c01fe1\",\"rct\":\"f699a6145ecc0f467a44e3450139722b6f8cb3076e6343f288c3012de31b8b70\"},{\"global_index\":\"7782206\",\"public_key\":\"0040623fb08f8c2549c28625a42e96a90a757a3ee27e84305ebffa3ee090ef11\",\"rct\":\"365a903dd6d779f46e530cb9b44cbe0cd4830d5ff51c5312fe0055336ce0ed08\"},{\"global_index\":\"7821004\",\"public_key\":\"932a6c85e8aa3d8addbad41a4728d1973f5b1b68ca206c0a0abc5942e8da792d\",\"rct\":\"78d94de809bbd2f223d15c058d61fc524139d10ce289075f5240890d77d706a3\"},{\"global_index\":\"7864246\",\"public_key\":\"59f7adbbe06765e0d5e85f15977f980d148027a7e13e4c1f4562f37c84210a07\",\"rct\":\"2f3ccc3bba4da09bd6fab4309b5767be4088d6fa8555c6886a9867c819de61c7\"},{\"global_index\":\"7864612\",\"public_key\":\"f8bbb33b4281fd2b328807d30844973775f8fef10a2898e181555bdce376ff77\",\"rct\":\"be562e9339c5601cd0311dae06796cde323d38f32234d88bfaba19c872058be1\"},{\"global_index\":\"7870461\",\"public_key\":\"273439a2d1421b3b4176fdcb3f79b93263db739adebd285cc8cd78f7f9cb8d08\",\"rct\":\"94610f3b1d7abe5973a711431b4f66248273fff7e8eef7f13c5427510f03d4ca\"},{\"global_index\":\"7876839\",\"public_key\":\"93394fc6d4d1449c61c19b86554985c20182d7ba821ffd73a6f9a1268d58f717\",\"rct\":\"b20123df818eedf914ddbda1f6cfc1ead9d20de2b9f15488af34151d1e531446\"},{\"global_index\":\"7880529\",\"public_key\":\"218300a9dc6420e7a9988a36ed4b4d52d49bc91ef6b77f690cc80762ae6c43bb\",\"rct\":\"b3138df6498ef50009e2567d5b21b61769c6a4de0c651a82bec1dd057291e697\"},{\"global_index\":\"7883788\",\"public_key\":\"598ecaf8a68d90f4d30fe0085cad2e8dc61c309bd1c009a693c7d1fc9eec3f34\",\"rct\":\"c65d0043ac5751e3969c8ed79af00a8d4988fc1660f7bcb586ed9b331d20948a\"},{\"global_index\":\"7886221\",\"public_key\":\"ae822bd7a5811fad23d79696b4776808275da2f68b2e01128ed471bb220347f5\",\"rct\":\"ce6830c0164841f6fbab4497299ed6810090089d05aa4981ac4e871838630a09\"},{\"global_index\":\"7871286\",\"public_key\":\"95ebe5288a34ee88c6bcd1f568ee5f2b1cbedd7eb11a705c4bfee4340c74d7c0\",\"rct\":\"71eb178f0a71931685a4f2f52a0c49b5d7f9e5989d4763ba3f1f0bca4cd5cfc1\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"4213160\",\"public_key\":\"3b6bc7838b6c581d9b385d3d749e80aba2e24dec0d779c9163cc08dd09761e14\",\"rct\":\"d07ee9f4068da6f1991d0c0a3b0c421fc6aea892af2e61f09f74c369c9cd742d\"},{\"global_index\":\"7594921\",\"public_key\":\"ca8b15f823c073bcb0da600104923d805b8e88c5bb82834bfa6a64c24e94d0d8\",\"rct\":\"61cf1e6f1822282123342b9074b42a744ed07f004afffc342c2a4f0b5751b90e\"},{\"global_index\":\"7744484\",\"public_key\":\"d3b113e786e6781fb3744cad1d12552274c3ccafb03e20d20caffc67a841b617\",\"rct\":\"2bc9b7bb8e56222875a8cf692224f41a7d11326d5af0ca198851a67b47315a66\"},{\"global_index\":\"7801628\",\"public_key\":\"3d3481cf34f66172b4012c1c6a6c0f996b878694cf6a4cc895f3631b67c40e76\",\"rct\":\"3925e560f04e935552398905a77775d7301d1f11d5425cc00f132717c1443025\"},{\"global_index\":\"7849322\",\"public_key\":\"a15ff0ffd989f5843c733dbefae105cec63910c443a616bc25e16ed87d15fee6\",\"rct\":\"d5b49880a4eb32add42cd9cc1f1d7900c0df08b323272a0a5eea55050e09cae2\"},{\"global_index\":\"7851464\",\"public_key\":\"2e49ed890adff562ce9f42d60e18138eeba3cbb61369fab808d57a58d598a672\",\"rct\":\"6a24f1733d1ce12bd4113ca7c95e704546203678a114ae39956f6a505018ecfd\"},{\"global_index\":\"7864819\",\"public_key\":\"c6f9506eaa56f96121d7c4e1b89b4658a6d19fc9f38a4c66017d2bf483ab5431\",\"rct\":\"b6a45256f22286f564e26a5a49979903d5e4add0e4d59f6dada463527e7696de\"},{\"global_index\":\"7865118\",\"public_key\":\"06f7003472cd99ed9c4c6adf10a5d9b68d0d166d75fb5176c3a60c1f73672545\",\"rct\":\"52ba8fea5b4ae56e7950c3a4e6f55350fe051a9344445f6cfad9a22fcaafda97\"},{\"global_index\":\"7865375\",\"public_key\":\"9ad8a2d0564319f2933f03c2d4ad82b386359c91f3cd31b3843fd83aa4deb5c2\",\"rct\":\"bd5377e338abd8379d35330b2adc9b875b66c23ae01ce589ccc238cc5386bb97\"},{\"global_index\":\"7867089\",\"public_key\":\"2f03d20a7c25b8520548fda84aef84dc68aa73e219a60d3095aaec52458f6cfa\",\"rct\":\"2c9986c71e5db8f4b52d5cc9eedb53b931fd25b475424033783a8158dce2ef38\"},{\"global_index\":\"7871345\",\"public_key\":\"84b90a1d2d1c77496bd44452e737b7744e123f114caedf384265003bc080c1be\",\"rct\":\"79589522d089ae98f87145a9d5dad888f901651dcd8604c58db9cca59d313e25\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6279342\",\"public_key\":\"7c27f3ed2e26ad513cd1f37356ee8f7df34d9181c8fbe2ae004340da4f1a7c9d\",\"rct\":\"9ded419f365d767c949d6c0ac69e15b6be1ef313846b86221e246a547daedade\"},{\"global_index\":\"7742464\",\"public_key\":\"dc80953501b4e520ba8d78881fb6b75b2a00f2226e18edd7b130f06b318181e8\",\"rct\":\"7ce50c73b53ea57d9fd739077803260ae93a335bb2e7032f78c92fa1966b8eae\"},{\"global_index\":\"7811834\",\"public_key\":\"fe84b7bc995f6b06df528f56f3fe7d67b746378e6c617d5b114c2efc9398e2c4\",\"rct\":\"0f783d4da4265c56da9f9880edbc75c6eb6037146da847cadd16c3818c17ed4c\"},{\"global_index\":\"7820872\",\"public_key\":\"39aa68039e4c60023bfa40d29dba245bf91f8c76c7308397b03dd2492356e0e1\",\"rct\":\"ecafe66a45459898e51bdcbbdd034c9f66e078c2e0bf9d961474e6d9fdf144ee\"},{\"global_index\":\"7822687\",\"public_key\":\"2d0e2b77e91e7b27e69e203471b726938e46c03d9c86ae030e20969fac1f086b\",\"rct\":\"39b3a494ee853c3f83ff845004c7853e001b21040b2045710a1bb7e648668393\"},{\"global_index\":\"7862258\",\"public_key\":\"65c68ccc0333481759a6c241c11508b2fb60d2e19cdf12441dd3f81d902bd11f\",\"rct\":\"788089eefcdcb5a63dd858e191347ae02b8866a5fbdc246832c3715f1d67a532\"},{\"global_index\":\"7867376\",\"public_key\":\"52c2155eed0b4317d01b3a2fe686554d678bd3d04b90d8d1ee632868ad9c1950\",\"rct\":\"a0687d61048ebc242b5debf1051f018179bc49722df9a6e3065f3eea88e2ecee\"},{\"global_index\":\"7874309\",\"public_key\":\"1bb35a6e9031b981242fabb4ca4944caf8d0ea14534e2582c9ad1207d08a7ea7\",\"rct\":\"18e9698082c8dc5c6de38607b6d0b2e3288ef3ad3d2362fca9117eda3a29e2ae\"},{\"global_index\":\"7877775\",\"public_key\":\"2b0e14f0a73fbd9d3655483cf6609941a221890ee449bb71ed9ed7f81ac79270\",\"rct\":\"48208839d6871147716129cb4227b4ed7754a54452233e5a19b9f864faac061c\"},{\"global_index\":\"7879466\",\"public_key\":\"d88404c1800564e112d942e6b516029aca09dd6da05f1317f2dca6b6ec2b6401\",\"rct\":\"8f81bcece8fa183c55081064d01f56ac3f8ea7f1a1f568b2fd7dc7ff3cf60257\"},{\"global_index\":\"7881671\",\"public_key\":\"9ed17e0648559062339a88a223863d8d6cdde2908cae3cdd39d8b7cfcffcfd2c\",\"rct\":\"4c5608f5bb111f66838de647a6e752866eccb28c27167360fa2a87abbd0e8b79\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"5789405\",\"public_key\":\"083eca3af06c5e598076ccf07420d6f0cc019f5d1a4815e148ac29c7c6e01ef5\",\"rct\":\"9a9a7752826682862cbd9d0e984db8e8170d9c1f3983d3ac33386dc0f7ee1db0\"},{\"global_index\":\"6170431\",\"public_key\":\"c62cc12a32618a88d2171f9940d80e5b3e75476e0c34d46fb42043150f4522aa\",\"rct\":\"d02db2acdcdaeb523f0f59615bffe60fb31b3f402f4f3a780317ea785a5fda55\"},{\"global_index\":\"7554990\",\"public_key\":\"654a7e72889996081d47c408f33fc53db5f1de0d30826c62dd15e2f4a311c871\",\"rct\":\"6709e9b8cfd3dd19052944827b73951c30c857702eae2759c58dd6fbdbc326da\"},{\"global_index\":\"7684795\",\"public_key\":\"2687e37e41bdb4cb511a15d47ca4fd8df3240f4665dc0f2340ef23334f6e850a\",\"rct\":\"af1e079aaa6fee300b9f3f4699e77de432e33f54b242dd59051287902122757e\"},{\"global_index\":\"7731766\",\"public_key\":\"ac5e84488a529e6a7723f446612cb518469a25e3f58bf4a2f5012566045c1c5e\",\"rct\":\"ecd8e8285b9485980d974fc43c2b98e7c4aebfb35af143cc3f008f249ac78002\"},{\"global_index\":\"7828341\",\"public_key\":\"545e2d7795ee1863d4745e5fb4e01e4b7e01796f22bd8086ef3d643c11bcee4a\",\"rct\":\"0233e8b05ec6c175099192d0ad3f8bcf68133350995a7c6a2aae4b02a08f405a\"},{\"global_index\":\"7855018\",\"public_key\":\"e7ee2fb3f1cf64cbb089b3c4ca49e0d123e0d6a48ed850cf157620499f485ef6\",\"rct\":\"060fab70166a043fad5f97f7600691d06b484ad56c676c108c9e8e4b981edc7f\"},{\"global_index\":\"7870548\",\"public_key\":\"1209a4478b27dfa990341c9fc17e9d07ef81097526ac1fd3661752aebdca0275\",\"rct\":\"2ac0abd594174fd120def42f88947dfaf8ef948fb2e96c6b443150e65df25a2a\"},{\"global_index\":\"7874679\",\"public_key\":\"bf2d9b60ccc856a0563d74e7a4b967718929ad9987ff01f5ec951b34e7ad2145\",\"rct\":\"68536e6b05cf595dc654565106001ca61a094d282cedad4a5824a5829ad78c9e\"},{\"global_index\":\"7880684\",\"public_key\":\"3a2ac4ee250b811e49fcb2b474b69a241463ac65d448d63fbe2dd5955401546e\",\"rct\":\"4aee28d936d8e346dee326ac502e49d732a2606ab00b1245a9aa8185beefb6ea\"},{\"global_index\":\"7885337\",\"public_key\":\"c98106a42af16c0db1d80b6e4143bcb2bda2ff87b0e78ad9783559a49a508c1c\",\"rct\":\"cd8295a8d1917cc221af043f61f5607372229bc9f784ab3114a6c84a20bbf9fe\"}]},{\"amount\":\"0\",\"outputs\":[{\"global_index\":\"6839007\",\"public_key\":\"75ceef04c9f9ebcdb0f7593ac28e02acb8886b12cefeb9fa5346b04157d71857\",\"rct\":\"0d7feec72e6766b97269e76545fd4e1b2deb5d9a55ec4c3afc1f4f4fb507ff34\"},{\"global_index\":\"7550322\",\"public_key\":\"d8d73a898974bc97eabb281650e3af4ab0621d6e936b064ae8075de7f6566145\",\"rct\":\"be615763ea49eb6f206963a3e124e70250477de0dadcec292c98281ef8fa6797\"},{\"global_index\":\"7778293\",\"public_key\":\"a4a5c9ecd365ef8fda20ee0ab75fe7e5a55c5489d596b73734b6defd8bc1a198\",\"rct\":\"523d2a48e6b625c0424e37f0679b7ef87a4526aa9d61e903aa85503722d47404\"},{\"global_index\":\"7864264\",\"public_key\":\"705eaf1c3081c3ee83c400f5bc847851e83bffbb3db62d386c4ecb5e413f84f4\",\"rct\":\"fcdc1a4b5679349f0233bd2034802c8d082e03d0771a940e6beeb5532f7743fa\"},{\"global_index\":\"7865825\",\"public_key\":\"dfc9097def2e62883b3f1fac947da7f1e941e4f295368fb3530e259868573a52\",\"rct\":\"d9c06528be92f435e687acdc82e7d56fa08a02a02d02d1a9bc798971de87692d\"},{\"global_index\":\"7880681\",\"public_key\":\"1af2a58f9301bcbf1bdd8528ac1b6468043c6083c21e53b0c3e0a97074fba06a\",\"rct\":\"50a00467fefcc760c191ff58ca481cddf98a02a9d9104ca93b29f9cc9524af97\"},{\"global_index\":\"7881660\",\"public_key\":\"515f2282c37c96bccfa961e8f245923091b077a367269522309911549a703e4e\",\"rct\":\"75b5c0219afa83fdae7db4557847572966f5b987b27171ca8eecfb43961a1585\"},{\"global_index\":\"7883765\",\"public_key\":\"fdc7adc6532d2daa55d4978ef02bdeac27e621cc5b384dd8ec8a61633f077f38\",\"rct\":\"fb98c508f33e5595808ad9bc903bce144917c7b33e8211cf641268288a5a3a56\"},{\"global_index\":\"7884228\",\"public_key\":\"5f4e509fcfde70795eaa9d6a438390d62d7fcb18c04a41ed209533d65e62c17a\",\"rct\":\"e5c4b9cc88d9879d2f1f08b6714c5e393510913123ff3448635cb89520e56c2c\"},{\"global_index\":\"7885897\",\"public_key\":\"2e96f758d91fc89ba845f294ae5df957a3e3b85960a718837e09991faa802c48\",\"rct\":\"5bc2cabc0c0ced1ebc0c62e78615cb42a311a67de4f947627be96460974ee7fb\"},{\"global_index\":\"6274109\",\"public_key\":\"09e9e6356621c9c8b61fcc9befe64318d5c9f4cedce0d9e532bfe646cc5cc5ec\",\"rct\":\"eb49b4e4c99cdb86325d4546c84f7e8823c453d01ffe378df3d270d7593a993a\"}]}]}";
//
string _send_routine__sweep_submitRawTx_dummyReplyJSONStr = "{}";
