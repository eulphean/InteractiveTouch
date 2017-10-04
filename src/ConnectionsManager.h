// Author: Amay Kataria
// Date: 10/3/2017
// Description: Defines a singleton instance of the ConnectionsManager, which will handle all
// the Connection instances. Depending on the complexity of the program, we'll use this. 

#pragma once

#include "ofMain.h"
#include "Connection.h"

class ConnectionsManager {
  static ConnectionsManager * _instance;

  // Collection of all the connections.
  vector<Connection> _connections;
  
  public:
    static ConnectionsManager * instance()
    {
      if (_instance == NULL) {
        _instance = new ConnectionsManager();
      }
      return _instance;
    }
  
    // Create a new connection.
    void createConnection();
};
