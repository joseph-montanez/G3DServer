/*
Copyright (c) 2009-2010, Joseph Montanez
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of the Joseph Montanez nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

var directory = new java.io.File('.');

var filter = new java.io.FilenameFilter({
    accept: function(file, name) {
        name = name.toLowerCase();
        return !name.startsWith(".") && (
        name.endsWith(".html") || name.endsWith(".htm") && 
        file.canRead() && file.isFile()
        );
    }
});

var files = directory.listFiles(filter);
var controllers = [];
for each(var file in files) {
    var file = new java.io.File(file);
    var filename = (file.getName() + "").split(".")[0];
    var functionName = filename.toUpperCase().substr(0, 1) + filename.substr(1, filename.length);
    
    var stream = new java.io.FileInputStream(file);
    var buffer = new java.io.BufferedInputStream(stream);
    var data = new java.io.DataInputStream(buffer);
    var str = "";

    while(data.available() != 0) {
        str += data.readLine() + "\n";
    }
    
    var printOpen = false;
    var printOpenSyntax = "[=";
    var printCloseSyntax = "]";
    
    var codeOpen = false;
    var codeOpenSyntax = "[";
    var codeCloseSyntax = "]";
    
    
    var Block = function (type) {
        this.startIndex = 0;
        this.endIndex = 0;
        this.data = "";
        this.type = type;
        return this;
    };
    var currentPrintBlock, currentStringBlock, currentCodeBlock, outside;
    outside = "";
    var blocks = [];
    for(var i = 0; i < str.length; i++) {
        var printOpenHint, printCloseHint;
        var codeOpenHint, codeCloseHint;
        
        printOpenHint = str.substr(i, printOpenSyntax.length); 
        printCloseHint = str.substr(i, printCloseSyntax.length); 
        
        codeOpenHint = str.substr(i, codeOpenSyntax.length); 
        codeCloseHint = str.substr(i, codeCloseSyntax.length); 
        
        if(codeOpen === false && printOpen === false && printOpenHint !== printOpenSyntax && codeOpenHint !== codeOpenSyntax) {
            outside += str[i];
        } else if(printOpenHint === printOpenSyntax && printOpen === false && codeOpen === false) {
            printOpen = true;
            
            currentStringBlock = new Block("string");
            currentStringBlock.data = outside;
            blocks.push(currentStringBlock);
            outside = "";
            
            currentPrintBlock = new Block("print");
            currentPrintBlock.startIndex = i;
        } else if(printCloseHint === printCloseSyntax && printOpen === true) {
            printOpen = false;
            currentPrintBlock.endIndex = i;
            currentPrintBlock.data = str.substr(
                currentPrintBlock.startIndex + printOpenSyntax.length, 
                currentPrintBlock.endIndex - currentPrintBlock.startIndex - printOpenSyntax.length
            );
            blocks.push(currentPrintBlock);
        } else if(codeOpenHint === codeOpenSyntax && codeOpen === false && printOpen === false) {
            codeOpen = true;
            
            currentStringBlock = new Block("string");
            currentStringBlock.data = outside;
            blocks.push(currentStringBlock);
            outside = "";
            
            currentCodeBlock = new Block("code");
            currentCodeBlock.startIndex = i;
        } else if(codeCloseHint === codeCloseSyntax && codeOpen === true) {
            codeOpen = false;
            currentCodeBlock.endIndex = i;
            currentCodeBlock.data = str.substr(
                currentCodeBlock.startIndex + codeOpenSyntax.length, 
                currentCodeBlock.endIndex - currentCodeBlock.startIndex - codeOpenSyntax.length
            );
            blocks.push(currentCodeBlock);
        }
    }
    if(outside.length > 0) {
        currentStringBlock = new Block("string");
        currentStringBlock.data = outside;
        blocks.push(currentStringBlock);
        outside = "";
    }
    

    out =  '#include <string>\n'+
           '#include "g3dserver/WebString.h"\n'+
           '#include "g3dserver/WebController.h"\n\n'+
           'class ' + functionName + 'Controller : public WebController {\n'+
           'public:\n'+
           '    void get() {\n';
    var indent = "        ";
    for(var i =0; i < blocks.length; i++) {
        var block = blocks[i];
        var data = (new java.lang.String(block.data)).trim();
        
        if(data < 1) {
            continue;
        }
        
        if(block.type === "string") {
            data = (new java.lang.String(block.data)).replace("\"", "\\\"");
            out += indent + "this->response->print(R\"delimiter(" + data + ")delimiter\");\n";
        } else if(block.type === "print") {
            out += indent + "this->response->print(" + block.data + ");\n";
        } else if(block.type === "code") {
            data = data.replace("):", ") {").replace("endfor", "}");
            if(data.indexOf("#include") > -1) {
                out = data + "\n" + out;
            } else if(data.indexOf("@page") > -1) {
                controllers.push([
                    data.replace("@page=", ""),
                    functionName,
                    filename + ".cpp"
                ]);
            } else {
                if(data.indexOf("}") === -1 && data.indexOf("{") === -1 && data.substr(-1) !== ";") {
                    data += ";";
                }
                out += indent + data + "\n";
            }
        }
    }

    out += "\n    }\n};";
    
    fstream = new java.io.FileWriter(filename + ".cpp");
    writer = new java.io.BufferedWriter(fstream);
    writer.write(out);
    writer.close();

    print(out);
}

var main = "";
main = 
    "#include <string>\n" +
    "#include \"g3dserver/WebServer.h\"\n";
for(var i = 0; i < controllers.length; i++) {
    var cont = controllers[i];
    main += "#include \"" + cont[2] + "\"\n";
}

main += "\n" +
    "int main(int argc, char* argv[]) {\n" +
    "    WebServer* server = new WebServer();\n\n" +
    "    server->port = 8181;\n";
    
for(var i = 0; i < controllers.length; i++) {
    var cont = controllers[i];
    main += "    server->addController(" + cont[0] + ", new " + cont[1] + "Controller());\n";
}

main +=
    "    server->run();\n" +
    "    delete server;\n" +
    "    return 0;\n" +
    "}";
print(main);


fstream = new java.io.FileWriter("main.cpp");
writer = new java.io.BufferedWriter(fstream);
writer.write(main);
writer.close();
