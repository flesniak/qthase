#ifndef TEXTS_H
#define TEXTS_H

#include <QString>

namespace text {

static const QString startupText = "\
<html>\n\
    <head>\n\
        <title>Hello World</title>\n\
        <script type=\"text/javascript\">\n\
            function a() {\n\
                field.value = \"Hello World\";\n\
            }\n\
        </script>\n\
    </head>\n\
    <body>\n\
        <input type=\"text\" id=\"field\"/><br/>\n\
        <button onclick=\"a()\">Click me!</button>\n\
    </body>\n\
</html>";

};

#endif // TEXTS_H
