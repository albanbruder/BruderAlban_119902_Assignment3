#include "graph.hpp"
#include "djikstra.hpp"

#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  Graph graph;

  auto augsburg         = graph.add("Augsburg");
  auto berlin           = graph.add("Berlin");
  auto braunschweig     = graph.add("Braunschweig");
  auto bremen           = graph.add("Bremen");
  auto dortmund         = graph.add("Dortmund");
  auto duesseldorf      = graph.add("Düsseldorf");
  auto freiburg         = graph.add("Freiburg");
  auto erfurt           = graph.add("Erfurt");
  auto frankfurt        = graph.add("Frankfurt");
  auto gelsenkirchen    = graph.add("Gelsenkirchen");
  auto hannover         = graph.add("Hannover");
  auto jena             = graph.add("Jena");
  auto leipzig          = graph.add("Leipzig");
  auto mainz            = graph.add("Mainz");
  auto mannheim         = graph.add("Mannheim");
  auto moenchengladbach = graph.add("Mönchengladbach");
  auto muenchen         = graph.add("München");
  auto nuernberg        = graph.add("Nürnberg");
  auto stuttgart        = graph.add("Stuttgart");
  auto weimar           = graph.add("Weimar");
  auto wuppertal        = graph.add("Wuppertal");

  augsburg->connect(stuttgart, 164);
  augsburg->connect(muenchen, 79);

  berlin->connect(hannover, 300);
  berlin->connect(braunschweig, 227);
  berlin->connect(leipzig, 190);

  bremen->connect(hannover, 127);

  dortmund->connect(wuppertal, 70);
  dortmund->connect(bremen, 234);

  duesseldorf->connect(moenchengladbach, 85);
  duesseldorf->connect(mainz, 185);

  freiburg->connect(mannheim, 194);
  freiburg->connect(bremen, 1250);

  erfurt->connect(frankfurt, 262);
  erfurt->connect(berlin, 237);
  erfurt->connect(weimar, 23);

  frankfurt->connect(mainz, 43);
  frankfurt->connect(duesseldorf, 196);
  frankfurt->connect(nuernberg, 224);
  frankfurt->connect(hannover, 573);

  gelsenkirchen->connect(dortmund, 35);

  hannover->connect(dortmund, 211);
  hannover->connect(braunschweig, 88);

  jena->connect(nuernberg, 226);

  leipzig->connect(jena, 105);

  mainz->connect(mannheim, 124);

  mannheim->connect(frankfurt, 124);

  moenchengladbach->connect(wuppertal, 33);

  muenchen->connect(freiburg, 351);
  muenchen->connect(nuernberg, 169);
  muenchen->connect(berlin, 840);

  nuernberg->connect(augsburg, 148);
  nuernberg->connect(stuttgart, 210);

  stuttgart->connect(mannheim, 90);
  stuttgart->connect(freiburg, 206);

  weimar->connect(leipzig, 130);
  weimar->connect(jena, 23);

  wuppertal->connect(gelsenkirchen, 48);
  wuppertal->connect(duesseldorf, 53);

  Djikstra djikstra{ graph };

  std::vector<std::shared_ptr<GraphNode>> sources{berlin, braunschweig, mannheim};

  for(auto source : sources) {
    std::cout << "SOURCE: " << source->label() << std::endl << std::endl;

    djikstra.djikstra(source);

    for(auto node : graph.nodes()) {
      if(node == source) {
        continue;
      }

      auto path = djikstra.path(node);
      if(path.size() > 0) {
        std::cout << "Shortest path from " << source->label();
        std::cout << " to " << node->label() << " (" << node->distance() << "km):" << std::endl;

        for(auto wp : path) {
          if(wp == djikstra.source()) {
            continue;
          }

          std::cout << "  " << wp->parent()->label() << " --> " << wp->label();
          std::cout << " (" << (wp->distance() - wp->parent()->distance()) << "km)" << std::endl;
        }
        std::cout << std::endl;
      } else {
        std::cout << "No route found for connection " << source->label() << " --> " << node->label() << "." << std::endl << std::endl;
      }
    }
  }
}
