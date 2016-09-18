from flask import Flask
from flask_sqlalchemy import SQLAlchemy

builtin_list = list


db = SQLAlchemy()

def init_app(app):
    app.config.setdefault('SQLALCHEMY_TRACK_MODIFICATIONS', False)
    db.init_app(app)

def from_sql(row):
    """Translates a SQLAlchemy model instance into a dictionary"""
    data = row.__dict__.copy()
    data['id'] = row.id
    data.pop('_sa_instance_state')
    return data


class Video(db.Model):
   __tablename__ = 'videos'

   id = db.Column(db.Integer, primary_key=True)
   type = db.Column(db.String(255))
   url = db.Column(db.String(255))
   duration = db.Column(db.Integer)

   def __repr(self):
       return "<Video(id='%s', type='%s', url='%s'" % (self.id, self.type, self.url)

def read(id):
    result = Video.query.get(id)
    if not result:
        return None
    return from_sql(result)

def create(data):
    video = Video(**data)
    db.session.add(video)
    db.session.commit()
    return from_sql(video)

def update(data, id):
    video = Video.query.get(id)
    for k, v in data.items():
        setattr(video, k, v)

    db.session.commit()
    return from_sql(video)

def delete(id):
    Video.query.filter_by(id=id).delete()
    db.session.commit()

def _create_database():
    app = Flask(__name__)
    app.config.from_pyfile('../config.py')
    init_app(app)
    with app.app_context():
        db.create_all()
    print("All tables created")


if __name__ == '__main__':
    _create_database()
