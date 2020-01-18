#include "json.hpp"
using json = nlohmann::json;
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    json j2 = {{"pi", 3.141},
               {"happy", true},
               {"name", "Niels"},
               {"address", "Your address"},
               {"nothing", nullptr},
               {"answer", {{"everything", (unsigned long)-1}}},
               {"list", {1, 0, 2}},
               {"object", {{"currency", "USD"}, {"value", 42.99}}}};

    std::cout << j2.dump(4) << std::endl;
    std::string jsonStr = j2.dump(4);

    json j = json::parse(jsonStr);

    auto everVal = j["answer"]["everything"];
    std::cout << "typename = " << (int)everVal.type() << std::endl;
    if (everVal.is_number()) {
        std::cout << "everything = " << everVal << std::endl;
    } else {
        std::cout << "is null" << std::endl;
    }

    if (j.is_object()) {
        for (auto it = j.begin(); it != j.end(); ++it) {
            std::cout << it.key() << ": " << it.value() << std::endl;
        }
    }

    return 0;
}
