#include "sqlite3.h"
#include "string"
#include <fstream>

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
                
                // Check if a file was uploaded
                if (this->request->hasFile("file1")) {
                    WebBoundary boundary = this->request->getFile("file1");
                    std::string data = boundary.getData();
                    // Save the data to file 
                    fstream file;
                    // You'll need to roll your own detection for which mimetype 
                    // for binary / pure text writes 
                    file.open(boundary.filename.c_str(), ios::out | ios::binary);
                    if (file.is_open()) {
                        file.write(data.data(), data.length());
                    } else {
                        content.append("<p>Cannot Open File!</p>");
                    }
                    file.close();
                    content.append("<p>\
                        You have uploaded " + boundary.filename + " to our server\
                        <br /> It was a  " + boundary.contentType + ", maybe...\
                        As you never want to trust input controllerable by the \
                        user.\
                    </p>");
                } else {
                    content.append("<p>Still Working on it huh? Comon upload a file!</p>");
                }
                
                content.append("\
                    <form method=\"post\" enctype=\"multipart/form-data\">\
                        <input type=\"file\" name=\"file1\" />\
                        <input type=\"file\" name=\"file2\" />\
                        <input type=\"submit\" value=\"Upload\" />\
                    </form>\
                ");

                this->append(content);
                this->append(admin::layout::footer());
            }
        };
    }
}
