import logging
import model
from flask import current_app, Flask, redirect, url_for, request, jsonify
from model import Video

def create_app(config, debug=False, testing=False, config_overrides=None):
    app = Flask(__name__)
    app.config.from_object(config)

    app.debug = debug
    app.testing = testing

    if config_overrides:
        app.config.update(config_overrides)

    # Configure logging
    if not app.testing:
        logging.basicConfig(level=logging.INFO)

    # Setup the data model.
    with app.app_context():
        model = get_model()
        model.init_app(app)

    # Add a default root route.
    @app.route("/")
    def index():
        return 

    # Add an error handler. This is useful for debugging the live application,
    # however, you should disable the output of the exception for production
    # applications.
    @app.errorhandler(500)
    def server_error(e):
        return """
        An internal error occurred: <pre>{}</pre>
        See logs for full stacktrace.
        """.format(e), 500

    current_video

    @app.route("/videos", methods=['GET'])
    def get_videos():
        sec = int(request.args.get('sec'), 0)
        result = Video.query.order_by('abs(duration - %d)' % sec ).limit(1).first()
        if result == None:
            return jsonify([])

        current_video = result.url
        return jsonify(result.serialize())

    @app.route("/recent", methods=['GET'])
    def watch_recent():
        return jsonify({
           'current': current_video
        })

    return app


def get_model():
    model_backend = current_app.config['DATA_BACKEND']
    if model_backend == 'cloudsql':
        from . import model
        model = model
    else:
        raise ValueError(
            "No appropriate databackend configured. "
            "Please specify datastore")

    return model
