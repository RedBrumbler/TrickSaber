#include "logging.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

Logger& getLogger() {
    static Logger* logger = new Logger({MOD_ID, VERSION}, {false, true});
    return *logger;
}
