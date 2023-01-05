# Simple DNS System
Project done within the scope of the curricular unit Communication by Computers @ University of Minho in 2022/23.

# How to use this:

## 1st version

In the src directory you'll find the modules _sp.py_, _ss.py_ and _client.py_.

The right way to test them is by using the testbed topology (_ambiente-teste.imn_) with CORE (Common Open Research Emulator).
This is a test for a simple MX query test from the client to a server.

1. Open ambiente-testes.imn with CORE;
2. Start the session;
3. Open bash (double-click) on 1 server and 1 client;
4. Run server (barreteSP in this case): `python3.10 /home/core/CC32/src/sp.py /home/core/CC32/config/config-barreteSP.txt 5353 255 debug`
5. Run client: `python3.10 /home/core/CC32/src/client.py 10.2.2.10 barrete.ccm. MX I`

## 2nd version

### Flux of DNS message

<p align="center"><img src="imgs/fluxo.png" width="100%" title="hover text"></p>

In the src directory you'll find the modules [sp](_sp.py_), [ss](_ss.py_), [sr](_sr.py_), [st](_st.py_), [sdt](_sdt.py_) and [client](_client.py_).

The right way to test them is by using the testbed [topology](_ambiente-teste.imn_) with CORE (Common Open Research Emulator).
This is a test for a simple NS query test from the client to a server.

1. Open ambiente-testes.imn with CORE;
2. Start the session;
3. Open bash (double-click) on 1 root, 1 resolution server, 1+ server(s) and 1 client;
4. Run resolution server: `python3.10 /home/core/CC32/src/sr.py /home/core/CC32/config/config-SR.txt /home/core/CC32/db/rootservers.txt 5353`
5. Run root server: `python3.10 /home/core/CC32/src/sp.py /home/core/CC32/config/config-root.txt 5353 255 debug`
6. Run domain server: `python3.10 /home/core/CC32/src/sp.py /home/core/CC32/config/config-bgjSP.txt 5353 255 debug`
7. Run sub-domain server: `python3.10 /home/core/CC32/src/ss.py /home/core/CC32/config/config-bgjSS.txt 5353 255 debug`
8. Run client: `python3.10 /home/core/CC32/src/client.py 10.4.4.13 .bgj. NS I`

## Test environment

<p align="center">
  <img src="imgs/ambienteteste.png" width="100%" title="hover text">
</p>