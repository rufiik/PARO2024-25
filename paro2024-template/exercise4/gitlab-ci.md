# PARO 2021 / Warsztat zwinnego programisty (CI, code review, pair programming, ATDD, zasady refaktoryzacji, itp.)
Instrukcja do laboratorium - Gitlab CI

Rafał Macyszyn <rafal.macyszyn@nokia.com>


## Wstęp

Gitlab (podobnie, jak konkurencyjny Github) jest usługą dostarczającą programistom pełne środowisko do tworzenia, rozwijania i utrzymywania projektów. Na potrzeby tego laboratorium wykorzystamy następujące funkcje:

  * przechowywanie kodu (Git)
  * Gitlab CI/CD
  * Gitlab Runners

W ramach darmowego konta, użytkownik otrzymuje 2000 minut CI/CD miesięcznie w usłudze *Gitlab Runners*. Dodatkowe minuty można dokupić, jednak na pewno nie będzie takiej konieczności – na potrzeby testowania zadań w tej instrukcji użyto około 5 bezpłatnych minut.


## Przygotowanie

### Przed wykonaniem zadań

Aby wykonać zadania z tej instrukcji, należy przygotować:

  * konto na *gitlab.com* - rejestracja pod linkiem: <https://gitlab.com/users/sign_in#register-pane>
  * dowolny edytor tekstowy (obsługa składni YAML ułatwia wykonanie zadania)
  * program Git (na Ubuntu/Debianie: `sudo apt-get install git`)
  * katalog z zadaniem z laboratorium

W celu zapoznania się z Gitem, można również dowolny artykuł wyjaśniający podstawy Gita (funkcje *clone*, *init*, *commit*, *add*, *pull*, *push*).


### Tworzenie projektu - Gitlab

Przed umieszczeniem kodu na Gitlabie należy utworzyć projekt.

Po zalogowaniu na Gitlaba, należy kliknąć zielony przycisk *New project* na głównej stronie *gitlab.com*, następnie ustawić nazwę projektu (np. `paro2021-lab`). Parametr *Visibility level* należy ustawić na *Public* - w przeciwnym przypadku projekt będzie widoczny jedynie dla tworzącego (i użytkowników przez niego wyznaczonych).

Mając nowo utworzony projekt, Gitlab podpowiada komendy, które można użyć, żeby umieścić na serwerze kod. Interesować nas będzie sekcja *Push an existing folder*, ponieważ katalog z kodem już istnieje, jednak nie jest on jeszcze śledzony w Gicie.


### Dodawanie plików projektu

Korzystając z gotowej instrukcji z Gitlaba (po kolei):

  * dodajemy obsługę Gita do aktualnego projektu,
  * informujemy Gita, do jakiego serwera chcemy synchronizować zmiany
  * dodajemy pliki do *staging area*, czyli zbioru zmian, z których zostanie utworzona rewizja (ang. *commit*)
  * tworzymy nową rewizję
  * synchronizujemy stan lokalnego repozytorium z serwerem

Przykładowa lista komend (**proszę korzystać z listy podanej przez Gitlaba**):

```
git init
git remote add origin git@gitlab.com:someone/some-project-name.git
git add .
git commit -m "Initial commit"
git push -u origin master
```

Po wykonaniu tych poleceń i odświeżeniu strony projektu, zobaczymy aktualną listę plików w projekcie.


## Gitlab CI

### Informacje wstępne

Każda zmiana pliku `.gitlab-ci.yml` wymaga stworzenie oddzielnej rewizji i umiesczenia jej na Gitlabie. Można to osiągnąć poleceniami:

```
git add zmienione/pliki.txt więcej/plików.txt oddzielam/spacją/inny.cpp .gitlab-ci.yml
git commit -m "opis zmian"
git push
```

Aktualny stan repozytorium można określić wpisując `git status`.

Aktualny stan zadań CI wyświetla zakładka *CI/CD* na stronie projektu. Można również otworzyć poszczególne *Pipeline*, aby zobaczyć, jakie zdania zostały wykonane. Po kliknięciu w zadanie (na wykresie) widać również szczegóły poszczególnych zadań.


### Stworzenie pliku .gitlab-ci.yml

**Uwaga 1:** Plik `.gitlab-ci.yml` ma na początku nazwy kropkę (patrz [dotfile])  
**Uwaga 2:** Format YAML korzysta z wcięć w postaci spacji. Konkretna "głębokość" wcięcia nie jest wymagana, natomiast najlepiej trzymać się jednej wybranej (i jej wielokrotności).  
**Uwaga 3:** Dla czytelności, w pliku YAML można umieścić dowolną liczbę pustych linii.  
**Uwaga 4:** W przypadku korzystania z *Git submodules* należy ustawić zmienną: `GIT_SUBMODULE_STRATEGY: recursive`

Plik `.gitlab-ci.yml` składa się z sekcji:

  * `image`: obraz Dockera użyty do obsługi Gitlab CI/CD
  * `stages`: lista faz CI
  * *dowolna inna nazwa*: zadanie CI

Dla uproszczenia, będziemy korzystać z gotowego obrazu udostępnionego na Gitlabie. W tym celu umieszczamy zmienną:

```yaml
image: registry.gitlab.com/rfmc/paro2021-docker
```

Tworzymy dwie fazy - `build`, w której skompilujemy testy, oraz `test`, w której wykonamy testy:

```yaml
stages:
  - build
  - test
```

### Faza *build*

W obrębie fazy `build` skonfigurujemy teraz jedno zadanie, również o nazwie `build`.  
Każde zadanie zawiera kilka zmiennych, które określają jego konfigurację:

  * `stage` - do jakiej fazy należy zadanie
  * `dependencies` - lista zależności (od myślników), które musza być wykonane, żeby zadanie mogło się rozpocząć
  * `variables` - dodatkowe zmienne (patrz *Uwaga 4*)
  * `script` - lista poleceń do wykonania w ramach zadania
  * `artifacts` - konfiguracja artefaktów zadania, z pod-zmiennymi:
      * `paths`: lista ścieżek, które zostaną zarchiwizowane
      * `when`: jedno z `on_success`, `on_failure`, `always` — określa, czy archiwizować artefakty, jeżeli zadanie zakończyło się niepowodzeniem

Przykładowa faza *build*:

```yaml
build:
  stage: build
  script:
    - mkdir build
    - cd build
    - cmake ..
    - make -j $(nproc)
  artifacts:
    expire_in: 1 hour
    paths:
      - build/application/Installer.exe
      - build
```

**W ramach tego zadania należy skonfigurować fazę *build* kompilującą projekt CMake (korzystając z przykładu) i archiwizującą katalog `build`.**

W przypadku większych projektów, archiwizowanie całego katalogu `build` z reguły jest złym pomysłem – katalog taki zawiera mnóstwo pozostałości po kompilacji, które można łatwo wygenerować ponownie. Ponadto Gitlab ogranicza rozmiar paczki z artefaktami do 1GB. W tym przypadku jednak będzie znacznie łatwiej spakować cały katalog, niż ręcznie określać, które pliki są warte przechowywania (lub użycia ich w późniejszych fazach).


### Zadanie 3c: faza *test*

**Uwaga 5:** Lista poleceń w części *script* jest wykonywana po kolei. Jeżeli którekolwiek z poleceń zakończy się błędem, wykonywanie zostanie przerwane.

W tej fazie korzystać będziemy z artefaktów wyprodukowanych przez fazę *build*. Skrypt w tym przypadku polega na uruchomieniu narzędzia `ctest`, które wykonuje testy skonfigurowanie w systemie CMake. Dodatkowo, możemy skorzystać z funkcji `reports`, która pobiera raport (np. w formacie jUnit) z wykonanych testów i prezentuje go razem z informacjami o zadaniu. Za wygenerowanie zawartości raportu w frameworku GoogleTest odpowiada przełącznik `--gtest_output=xml:nazwa_pliku.xml`, natomiast sekcja `reports:` informuje Gitlaba, że raport w formacie jUnit będzie dostępny w podanym pliku.

Narzędzie `ctest` pozwala na skonfigurowanie wcześniej zadanego zestawu testów, dzięki czemu nie trzeba ich ręcznie dodawać do konfiguracji CI. Dzięki temu projekt konfigurowany jest z jednego miejsca, co ogranicza możliwość omyłkowego stworzenia testu i nie dodania go do konfiguracji CI.

W konfiguracji projektu do laboratorium flaga `--gtest_output=...` została dołączona do konfiguracji narzędzia `ctest`.

Obecność katalogu `build/junit` i zawartych w nim plików można sprawdzić, kompilując projekt, następnie wykonując komendę `ctest --verbose`.

Przykładowy kod zadania:

```yaml
gtest:
  stage: test
  dependencies:
    - build
  script:
    - cd build
    - ctest --verbose
  artifacts:
    when: always
    reports:
      junit: build/junit/*.junit.xml
```

**W ramach tego zadania należy skonfigurować fazę *test*, zawierającą dwa zadania (np. *test-exercise1* i *test-exercise2*), wykonujące zestaw testów z danej części projektu**


### Zadanie 4: weryfikacja

Po skutecznym wykonaniu powyższych zadań, *Pipeline* powinno zawierać:

  * dwie fazy - *Build* i *Test*
  * w obrębie fazy *Build*:
      * jedno zadanie: *build*
  * w obrębie fazy *Test*:
      * jedno zadanie *gtest* wykonujące testy
  * wypełnioną sekcję *Tests*


[dotfiles]: https://en.wikipedia.org/wiki/Hidden_file_and_hidden_directory#Unix_and_Unix-like_environments
