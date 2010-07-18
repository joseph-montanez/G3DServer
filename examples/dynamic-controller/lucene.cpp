#include "../webserver/WebController.h"
#include "blog/layout.h"
#include "CLucene.h"

#include "string"
using namespace std;


class LuceneController : public WebController {
public:

    void get() {
        std::string                         index;
        std::string                         search;
        std::string                         field;
        std::string                         content;
        lucene::index::IndexReader          *reader;
        lucene::search::IndexSearcher       *searcher;
        lucene::search::Query               *query;
        lucene::search::Hits                *hits;
        lucene::analysis::WhitespaceAnalyzer analyser;  
        bool                                 hasHits;      
        
        index = "index";
        search = "ball";
        field = "summary";
        hasHits = false;
        
        reader = lucene::index::IndexReader::open(index.c_str(), false);
        searcher = new lucene::search::IndexSearcher(reader);
        try {
            query = lucene::queryParser::QueryParser::parse(L"ball", L"summary", &analyser);
            hits = searcher->search(query);
            hasHits = true;
        } catch (CLuceneError &error) {
            const char *what = error.what();
            content.append("Shit hit the fan!<br />");
            content.append(what);
            content.append("<br />");
        }
        
        if (hasHits && hits->length() > 0) {
            for(unsigned long i=0; i < hits->length(); i++) {
                content.append("1 FOUND: ");
                // Get the Doc
                lucene::document::Document &doc = hits->doc(i);
                // I hate widestring, must be a better way to convert!
                std::wstring name = doc.get(L"title");
                std::string title(name.begin(), name.end());
                title.assign(name.begin(), name.end());
                
                content.append(title);
                content.append("<br />");
            }
            delete hits;
            delete query;
        } else {
            content.append("GOT NO HITS");
        }
          
        reader->close();
        delete searcher;
        
        this->response->body.append(blog::layout::header("Gorilla Labs"));
        content.append(blog::layout::post("Hello World", "something", "You are running G3D Webserver 0.1a."));
        content = blog::layout::content(content);
        this->response->body.append(content);
        this->response->body.append(blog::layout::footer());
    }
};
