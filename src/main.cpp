#include <iostream>

#include <libsnark_helpers/libsnark_helpers.hpp>
#include <prover/prover.hpp>
#include <prover/computation.hpp>
#include <sha256/sha256_ethereum.hpp>

#include <cli/mainCmd.hpp>
#include <cli/setupCmd.hpp>
#include <cli/proveCmd.hpp>

int main(int argc, char* argv[]) {
    // The first argument is the executable itself, and the second is the command
    // The executable itself does nothing, we need to specify a command
    std::string program(argv[0]);
    if (argc < 2) {
        printUsage(program);
        return 1;
    }

    // Two commands supported
    // One to compute the trusted setup, the other one to compute proofs
    std::string command(argv[1]);
    if (command != "setup" && command != "prove") {
        std::cerr << "Unknown command" << std::endl;
        printUsage(program);
        return 1;
    }
    
    // See: https://github.com/scipr-lab/libff/blob/master/libff/algebra/curves/alt_bn128/alt_bn128_init.cpp
    libff::alt_bn128_pp::init_public_params();
    typedef libff::Fr<libff::alt_bn128_pp> FieldT;

    // Instantiate the prover
    Miximus<FieldT, sha256_ethereum> prover;

    switch (getCommandCode(command)) {
        case SETUP: setupCommand(prover);
                      break;
        case PROVE: proveCommand();
                      break;
        default: std::cerr << "Unknown command" << std::endl;
                 printUsage(program);
                 return 1;
    }

    return 0;

    //// Values given by the user
    //libff::bit_vector leaf = node16;
    //
    //libff::bit_vector address_bits;
    //address_bits = {0,0,0,0};
    //size_t address = 0;

    //std::vector<merkle_authentication_node> merkle_path;
    //merkle_path = {node3,node5,node9,node17};

    //const size_t tree_depth = 4;

    //bool valid_proof = prover.prove(merkle_path, secret, nullifier, leaf, node_root, address_bits, address, tree_depth);

    //if (!valid_proof) {
    //    std::cout << "Invalid proof" << std::endl;
    //    return 1;
    //}

    //std::cout << "Proof generated successfully" << std::endl;
}
