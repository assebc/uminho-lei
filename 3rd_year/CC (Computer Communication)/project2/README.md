# Simple DNS System
Project done within the scope of the curricular unit Communication by Computers @ University of Minho in 2022/23.

# How to use this:

In the src directory you'll find the modules _sp.py_, _ss.py_ and _client.py_.

The right way to test them is by using the testbed topology (_ambiente-teste.imn_) with CORE (Common Open Research Emulator).
This is a test for a simple MX query test from the client to a server.

1. Open ambiente-testes.imn with CORE;
2. Start the session;
3. Open bash (double-click) on 1 server and 1 client;
4. Run server (barreteSP in this case): `python3.10 /home/core/CC32/src/sp.py /home/core/CC32/config/config-barreteSP.txt 5353 255 debug`
5. Run client: `python3.10 /home/core/CC32/src/client.py 10.2.2.10 barrete.ccm. MX I`
