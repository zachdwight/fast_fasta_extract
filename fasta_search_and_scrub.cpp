#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <stdexcept> 
#include <vector>    


std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (std::string::npos == first) {
        return str; 
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

std::string getFastaSequenceById(const std::string& inputFilePath, const std::string& targetId) {
    std::map<std::string, std::string> sequences;
    std::string currentId;
    std::string currentSequenceBuffer;

    std::ifstream infile(inputFilePath);
    if (!infile.is_open()) {
        throw std::runtime_error("Error: Could not open input file: " + inputFilePath);
    }

    std::string line;
    while (std::getline(infile, line)) {
        line = trim(line); 

        if (line.empty()) {
            continue; 
        }

        if (line.rfind(">", 0) == 0) { 
            if (!currentId.empty() && !currentSequenceBuffer.empty()) {
                sequences[currentId] = currentSequenceBuffer;
            }
            currentId = line.substr(1); 
            currentSequenceBuffer.clear(); 
        } else {
           
            currentSequenceBuffer += line;
        }
    }

   
    if (!currentId.empty() && !currentSequenceBuffer.empty()) {
        sequences[currentId] = currentSequenceBuffer;
    }

   
    auto it = sequences.find(targetId);
    if (it != sequences.end()) {
        return it->second; 
    } else {
        return ""; 
    }
}

int main(int argc, char* argv[]) {
    
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_fasta_file> <target_sequence_id>" << std::endl;
        return 1; 
    }

    
    std::string inputFileName = argv[1];
    std::string targetSequenceId = argv[2];

    try {
        std::string sequence = getFastaSequenceById(inputFileName, targetSequenceId);

        if (!sequence.empty()) {
            std::cout << "Target " << targetSequenceId << ":\n" << sequence << std::endl;
        } else {
            std::cout << "Target " << targetSequenceId << " not found in the file." << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1; 
    }

    return 0; 
}
