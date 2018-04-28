#include "paramsmanager.hxx"

ParamsManager::ParamsManager(int argc, char **argv) {
    this->wired = false;
    this->filename = "";
    this->texture = "";
    this->output = "";
    this->mapping = FLAT;
    this->resolution = 35;

    if(argc == 1) {
        std:: cout << "To know all possibly flags use -h or --help to know all the flags" << std::endl;
    }

    if(argc == 2) {
        std::string key = argv[1];
        if(key == "-h" || key == "--help") {
            this->showHelp(argv[0]);
        } else {
            std::cerr << key << " is not a valid flag, use -h or --help to know all the flags" << std::endl;
            this->showHelp(argv[0]);
        }
    }

    for(int i = 1; i < argc; i+= 2) {
        std::string key = argv[i];
        std::string val = argv[i + 1];

        if(key == "-w" || key == "--wired") {
            if(val == "true" || val == "false") {
                this->wired = val == "true";
            } else {
                std::cerr << "wired param only accepts [true|false] values" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if(key == "-m" || key == "--mapping") {
            if(val == "flat") {
                this->mapping = FLAT;
            } else if (val == "gouraud") {
                this->mapping = GOURAUD;
            } else if(val == "phong") {
                this->mapping = PHONG;
            } else {
                std::cerr << "mapping param only accepts [flat|gouraud|phong] values" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if(key == "-t" || key == "--texture") {
            this->texture = val;
        } else if(key == "-f" || key == "--file") {
            this->filename = val;
        } else if(key == "-o" || key == "--output") {
            this->output = val;
        } else if(key == "-r" || key == "--resolution") {
            this->resolution = std::atoi(val.c_str());
            if(this->resolution < 15 || 50 < this->resolution) {
                std::cerr << "resolution must be between [15...50]" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {
            std::cerr << key << " is not a valid flag, use -h or --help to know all the flags" << std::endl;
            this->showHelp(argv[0]);
        }
    }
}

void ParamsManager::showHelp(const char* command) {
    std::cout << "Usage:" << std::endl;
    std::cout << command << " [params...]" << std::endl;
    std::cout << "\t" << "-w | --wired    Specify if the horse will be shown as a solid or wired" << std::endl;
    std::cout << "\t" << "                possibly values are [true|false]" << std::endl << std::endl;
    std::cout << "\t" << "-m | --mapping  Specify the type of mapping" << std::endl;
    std::cout << "\t" << "                possibly values are [flat|gouraud|phong]" << std::endl << std::endl;
    std::cout << "\t" << "-t | --texture  Specify the image to apply as texture" << std::endl << std::endl;
    std::cout << "\t" << "-f | --file     Specify the file where to load the points of the horse" << std::endl << std::endl;
    std::cout << "\t" << "-o | --output   Specify the file where to save the points of the horse" << std::endl << std::endl;
    exit(EXIT_FAILURE);
}