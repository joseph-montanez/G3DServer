#include "layout.h"
#include "../../webserver/WebController.h"

#include "string"
using namespace std;

namespace admin {

    class DashboardController : public WebController {
    public:

        void get() {
            string content;
            string admin_id = this->session->get("admin_id");
            bool logged_in = false;

            if (admin_id.length() > 0) {
                logged_in = true;
            }

            if (!logged_in) {
                this->response->setStatus(302);
                this->response->setHeader("location", "Location: /admin");
                return;
            }

            this->response->body.append(admin::layout::header("Blog Posts | Admin | Gorilla Labs", "dashboard", logged_in));
            content.append("TODO");

            this->response->body.append(content);
            this->response->body.append(admin::layout::footer());
        }
    };
}
