#include "window.hpp"
#include "textbox.hpp"

using namespace genv;
using namespace std;

class MainWindow : public Window {
    TextBox* t;
public:
    MainWindow() : Window(800, 600) {
        t = new TextBox(this, 25, 25, 250, "hello");
    }
    void event_handler(event ev) {}
};

int main() {
    MainWindow mw;
    return mw.event_loop();
}
