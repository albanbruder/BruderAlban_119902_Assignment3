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
  augsburg->connect(muenchen, 72);

  berlin->connect(hannover, 286);
  berlin->connect(braunschweig, 235);
  berlin->connect(leipzig, 190);

  bremen->connect(hannover, 137);

  dortmund->connect(wuppertal, 48);
  dortmund->connect(bremen, 236);

  duesseldorf->connect(moenchengladbach, 33);
  duesseldorf->connect(mainz, 218);

  freiburg->connect(mannheim, 199);
  freiburg->connect(bremen, 704);

  erfurt->connect(frankfurt, 257);
  erfurt->connect(berlin, 302);
  erfurt->connect(weimar, 23);

  frankfurt->connect(mainz, 43);
  frankfurt->connect(duesseldorf, 229);
  frankfurt->connect(nuernberg, 224);
  frankfurt->connect(hannover, 350);

  gelsenkirchen->connect(dortmund, 34);

  hannover->connect(dortmund, 212);
  hannover->connect(braunschweig, 66);

  jena->connect(nuernberg, 223);

  leipzig->connect(jena, 104);

  mainz->connect(mannheim, 83);

  mannheim->connect(frankfurt, 79);

  moenchengladbach->connect(wuppertal, 69);

  muenchen->connect(freiburg, 423);
  muenchen->connect(nuernberg, 169);
  muenchen->connect(berlin, 584);

  nuernberg->connect(augsburg, 146);
  nuernberg->connect(stuttgart, 200);

  stuttgart->connect(mannheim, 132);
  stuttgart->connect(freiburg, 205);

  weimar->connect(leipzig, 130);
  weimar->connect(jena, 22);

  wuppertal->connect(gelsenkirchen, 54);
  wuppertal->connect(duesseldorf, 32);

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
