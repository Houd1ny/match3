TGT:=match3
CXXFLAGS:=-O2 -std=c++14 -I libs/msm-lite/include -Ilibs/di/include -Ilibs/range-v3/include
CXXFLAGS_EMSCRIPTEN:=-Wwarn-absolute-paths --emrun -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2
CXXFLAGS_APP:=-I/usr/local/include/SDL2
LINKFLAGS_EMSCRIPTEN:=--preload-file data --use-preload-plugins
LINKFLAGS_APP:=-lSDL2 -lSDL2_image -lSDL2_ttf

all: app app_run

web:
	em++ $(CXXFLAGS) $(CXXFLAGS_EMSCRIPTEN) $(LINKFLAGS_EMSCRIPTEN) $(TGT).cpp -o index.html --shell-file template.html

web_run:
	emrun --port 8080 index.html

app:
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_APP) $(LINKFLAGS_APP) src/main.cpp -o $(TGT)

app_run:
	./$(TGT)

release: clean web
	git stash save && TMP=`mktemp -d /tmp/match.XXXX` && mv index.* $$TMP && git checkout gh-pages && mv $$TMP/index.* . && git add index.* && git commit -m "release" && git push origin +HEAD:gh-pages && git checkout master && rm -rf $$TMP && git stash pop

clean:
	rm -f index.* $(TGT)

test:
	$(CXX) $(CXXFLAGS) test.cpp -o test.out && ./test.out