import os

from library import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # Access input data from form
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Add(append) data to database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        # Return to homepage
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        # Query for all people in database along with their birthdays (should be displayed in table)
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render birthday data
        return render_template("index.html", birthdays=birthdays)
