"""
This file contains all of the configuration values for the application.
Update this file with the values for your specific Google Cloud project.
You can create and manage projects at https://console.developers.google.com
"""

import os

# The secret key is used by Flask to encrypt session cookies.
SECRET_KEY = 'secret'

# There are three different ways to store the data in the application.
# You can choose 'datastore', 'cloudsql', or 'mongodb'. Be sure to
# configure the respective settings for the one you choose below.
DATA_BACKEND = 'cloudsql'

# Google Cloud Project ID. This can be found on the 'Overview' page at
# https://console.developers.google.com
PROJECT_ID = os.environ['PROJECT_ID']

# Cloud Datastore dataset id, this is the same as your project id.
DATASTORE_DATASET_ID = PROJECT_ID

# SQLAlchemy configuration
# Replace user, pass, host, and database with the respective values of your
# Cloud SQL instance.
CLOUDSQL_USER = os.environ['CLOUDSQL_USER']

CLOUDSQL_PASSWORD = os.environ['CLOUDSQL_PASS']

CLOUDSQL_DATABASE = os.environ['CLOUDSQL_DB']

CLOUDSQL_CONNECTION_NAME = os.environ['CLOUDSQL_CONNECTION']

# SQL databases used by Google VM and local
LOCAL_SQLALCHEMY_DATABASE_URI = 'mysql+pymysql://{user}:{password}@localhost/{database}'.format(user = CLOUDSQL_USER, password = CLOUDSQL_PASSWORD, database = CLOUDSQL_DATABASE)

LIVE_SQLALCHEMY_DATABASE_URI = 'mysql+pymysql://{user}:{password}@localhost/{database}?unix_socket=/cloudsql/{connection_name}'.format(user = CLOUDSQL_USER, password = CLOUDSQL_PASSWORD, database = CLOUDSQL_DATABASE, connection_name = CLOUDSQL_CONNECTION_NAME)

if os.environ.get('GAE_APPENGINE_HOSTNAME'):
    SQLALCHEMY_DATABASE_URI = LIVE_SQLALCHEMY_DATABASE_URI
else:
    SQLALCHEMY_DATABASE_URI = LOCAL_SQLALCHEMY_DATABASE_URI

