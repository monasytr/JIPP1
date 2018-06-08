
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <streambuf>
#include <string>

// fragment strony: http://www.cutestpaw.com/articles/50-cute-cats-make-your-life-happier/
const std::string cats_file = "cats.html";

const std::string phys_data(R"(
Speed:	366
Mass:	35
Point: 50 70
Speed:	378
Mass:	32
Point: 25 35
Speed:	400
Mass:	30
Point: 23 16)");

struct Cat {
  std::string url;
  std::string title;
  std::string img_url;
};

void print(const Cat &cat) {
  std::cout << "Url: " << cat.url << ", title: " << cat.title
            << ", img_url: " << cat.img_url << '\n';
}

void print(const std::vector<Cat>& cats) {
  for (const auto& cat : cats) {
    print(cat);
  }
}
void print(const std::vector<std::string>& titles) {
  for (const auto& title : titles) {
    std::cout << "Title: " << title << '\n';
  }
}

std::string load_cats() {
  std::fstream stream_of_cats{cats_file};
  std::string cats_data{std::istreambuf_iterator<char>(stream_of_cats), {}};
  return cats_data;
}

//----------------------------------------------------------------------

void zadanie1() {

  // std::regex speed_regex(R"(Speed:[[:space:]]*([[:digit:]]*))");
  std::regex speed_regex("Speed:[[:space:]]*([[:digit:]]*)");
  // std::regex speed_regex(R"(Speed:\s*(\d*))");
  // std::regex speed_regex("Speed:\\s*(\\d*)");

  std::smatch sm;
  if (std::regex_search(phys_data, sm, speed_regex)) {
    std::cout << "Prefix> " << sm.prefix() << '\n';
    std::cout << "Full Match> " << sm[0]
              << '\n'; // zwraca cały dopasowany napis
    std::cout << "Match> " << sm[1]
              << '\n'; // zwraca pierwszą dopasowaną grupę (to w nawiasach () )
    // kolejne grupy znajdowałyby się pod indeksami 2, 3, itp.
    std::cout << "Suffix> " << sm.suffix() << '\n';
  }

  // Dopasuj i wyciągnij obie liczby przy "Point"
}

//----------------------------------------------------------------------

void zadanie2() {
  std::regex speed_regex("Speed:[[:space:]]*([[:digit:]]*)");

  std::smatch sm;

  auto data = phys_data;
  while (std::regex_search(data, sm, speed_regex)) {
    std::cout << "Prefix> " << sm.prefix() << '\n';
    std::cout << "Full Match> " << sm[0] << '\n';
    std::cout << "Match> " << sm[1]
              << '\n'; // 1, 2, 3, ,,, to są kolejne dopasowania grup.
    std::cout << "Suffix> " << sm.suffix() << '\n';
    std::cout << "------\n";

    data = sm.suffix(); // zastępuje wartość zmiennej 'data' tym co nie zostało jeszcze przeszukane
  }

  // Utwórz strukturę Point z dwoma polami x i y. Zaimplementuj funkcję
  // print.
  // Wczytaj wszystkie wymiary do tablicy struktur Point.
  // Powyższe zaimplementuj w funkcji, która będzie zwracała odpowiednią
  // kolekcję.
  // Patrz kod poniżej

  // std::vector<Point> points = parse_points(phys_data);
  // for (auto & point : points) {
  //   print(point);
  // }
}

//----------------------------------------------------------------------

std::vector<std::string> parse_titles(std::string data) {

  std::vector<std::string> titles;
  std::regex title_regex{"title=\"([[:alnum:][:space:]]*)\""};

  std::smatch title_match;
  while (std::regex_search(data, title_match, title_regex)) {
    titles.push_back(title_match[1]);

    data = title_match.suffix();
  }
  return titles;
}
//----------------------------------------------------------------------

std::vector<std::string> parse_titles_it(const std::string &data) {

  std::vector<std::string> titles;
  std::regex title_regex{"title=\"([[:alnum:][:space:]]*)\""};

  auto titles_begin = std::sregex_iterator(data.begin(), data.end(), title_regex);
  std::transform(titles_begin, {}, std::back_inserter(titles),
                 [](const std::smatch &sm) { return sm[1]; });

  return titles;
}
//----------------------------------------------------------------------

std::vector<Cat> parse_cats(std::string cats_data) {

  std::vector<Cat> cats;

  // TODO: zaimplementuj


  return cats;
}

//----------------------------------------------------------------------
void zadanie3() {

  // poniżej znajdują się wywołania dwóch różnych implementacji dopasowywania wzorców.
  // wyciągają one wszystkie atrybuty 'title', zarówno ze znaczników <a> jak i <img>
  // Dostosuj wyrażenia regularne,tak, wyciągać tytuł tylko ze znacznika 'img'.

  const auto cats_data = load_cats();
  {
    auto titles = parse_titles(cats_data);
    print(titles);
  }
  {
    auto titles = parse_titles_it(cats_data);
    print(titles);
  }

}
//----------------------------------------------------------------------

void zadanie4() {

  // zaimplementuj funkcję parse_cats wypełniającą kontener obiektów typu Cat.
  // Struktury Cat uzupełnij w następujący sposób:
  // url <- zawartość atrybutu href znacznika <a>
  // title <- zawartość atrybutu title znacznika <img>
  // img_url <- zawartość atrybutu src znacznika <img>

  const auto cats_data = load_cats();
  std::vector<Cat> cats = parse_cats(cats_data);
  print(cats);
}

int main() {

  zadanie1();
  zadanie2();
  zadanie3();
  zadanie4(); 


  return 0;
}
