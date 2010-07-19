#include "sqlite3.h"
#include "string"

#include "../../../webserver/WebController.h"
#include "../../../webserver/SqlRow.h"
#include "../../../webserver/SqlQuery.h"
#include "../layout.h"

using namespace std;

namespace admin {
    namespace blog {

        class CommentController : public WebController {
        public:

            void get() {
                string content;
                string admin_id = this->session->get("admin_id");
                bool logged_in = false;

                if (admin_id.length() > 0) {
                    logged_in = true;
                }

                if (!logged_in) {
                    this->response->setStatus(301);
                    this->response->setHeader("location", "Location: /admin");
                    return;
                }

                this->response->body.append(admin::layout::header("Blog Posts | Admin | Gorilla Labs", "blog-comments", logged_in));
                content.append("TODO");

                this->append(content);
                this->append(admin::layout::footer());
            }
        };
    }
}
