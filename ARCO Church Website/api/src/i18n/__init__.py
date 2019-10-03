from flask import Blueprint

i18n = Blueprint('i18n', __name__)

from . import api
