#include "sqlite3.h"
#include "string"

#include "../../../webserver/WebController.h"
#include "../../../webserver/SqlRow.h"
#include "../../../webserver/SqlQuery.h"
#include "../layout.h"

using namespace std;

namespace admin {
    namespace upload {

        class FormController : public WebController {
        public:

            void get() {
                string content;

                this->response->body.append(admin::layout::header("Example Uploading | Admin | Gorilla Labs", "blog-comments", true));
                content.append("\
                    <form method=\"post\" enctype=\"multipart/form-data\">\
                        <input type=\"file\" name=\"file\" />\
                        <input type=\"submit\" value=\"Upload\" />\
                    </form>\
                ");

                this->append(content);
                this->append(admin::layout::footer());
            }
        };
    }
}
