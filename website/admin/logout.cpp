#include "layout.h"
#include "../../webserver/WebController.h"

#include "string"
using namespace std;

namespace admin {

    class LogoutController : public WebController {
    public:

        void get() {
            this->session->unset("admin_id");

            this->response->setStatus(301);
            this->response->setHeader("location", "Location: /admin");
        }
    };

}
