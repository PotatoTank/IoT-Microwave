# REST API
This is the REST API that fetches an appropriate YouTube video for a given time (in seconds). What it does is minimize the distance between sucessive neighbours. In other words, it finds the closest neighbour.

The database is populated with a small initial seed sample of 500 of the top posts from [/r/videos](https://www.reddit.com/r/videos/top). No scraping is done by the API&mdash;all the API does is perform lookups against our server.

The Flask API was deployed on one of the Google Compute Engine VM profiles (Ubuntu 16.04 LTS).

## Deployment
Create and source these bash exports somewhere in your environment variables. I create a ``~/.bash_exports`` file and source it.

```bash
export PROJECT_ID=YourProjectIdHere
export CLOUDSQL_USER=CloudSQLUser
export CLOUDSQL_PASS=CloudSQLPassword
export CLOUDSQL_DB=CloudSQLDatabase
export CLOUDSQL_CONNECTION=CloudSQLConnection
```

The ``config.py`` file will read the environment variables.

You may also want to deploy the Flask app as a daemon.

To install dependencies, change directories to the ``api/`` directory, and then do

```bash
pip install -r requirements.txt
```
