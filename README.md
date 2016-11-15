<a href="http://www.boost.org/LICENSE_1_0.txt" target="_blank">![Boost Licence](http://img.shields.io/badge/license-boost-blue.svg)</a>
<a href="https://travis-ci.org/modern-cpp-examples/match3" target="_blank">![Build Status](https://img.shields.io/travis/modern-cpp-examples/match3/master.svg?label=linux)</a>
<a href="http://github.com/modern-cpp-examples/match3/issues" target="_blank">![Github Issues](https://img.shields.io/github/issues/modern-cpp-examples/match3.svg)</a>

---------------------------------------

#Simple Web Match3 game in C++14

<a href="http://modern-cpp-examples.github.io/match3">
  <img src="docs/match3.png" width="300" height="450"/>
</a>

###Tested Compilers

* Web
  * [Emscripten](emscripten.org)
  * [WebAssembly](http://webassembly.org)

* Desktop
  * [Clang-3.7+](http://clang.llvm.org)
  * [GCC-6+](https://gcc.gnu.org/gcc-6/changes.html)

###Dependencies

* [SDL2](https://www.libsdl.org/download-2.0.php)
* [Range-v3](https://github.com/ericniebler/range-v3)
* [Boost.DI](https://github.com/boost-experimental/di) (Proposed)
* [Boost.SML](https://github.com/boost-experimental/sml) (Proposed)


###Quick start

<table>
  <tr>
    <td></td>
    <td>Desktop</td>
    <td>Web</td>
  </tr>
  <tr>
    <td>Download</td>
    <td colspan="2"><code>git clone --recursive https://github.com/modern-cpp-examples/match3.git</code></td>
  </tr>
  <tr>
    <td>Compile</td>
    <td><code>mkdir build &amp;&amp; cmake .. &amp;&amp; make app</code></td>
    <td><code>mkdir build &amp;&amp; cxx=em++ cmake .. &amp;&amp; make web</code></td>
  </tr>
  <tr>
    <td>Run</td>
    <td><code>./match3</code></td>
    <td><code>$browser index.html</code></td>
  </tr>
</table>
