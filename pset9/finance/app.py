import os

from cs50 import SQL
from datetime import datetime, timezone
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from sys import stderr

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Create new table and index to track stock orders by each user
db.execute("CREATE TABLE IF NOT EXISTS orders (id INTEGER, user_id NUMERIC NOT NULL, symbol TEXT NOT NULL, \
            shares NUMERIC NOT NULL, price NUMERIC NOT NULL, timestamp TEXT, PRIMARY KEY(id), \
            FOREIGN KEY(user_id) REFERENCES users(id))")
db.execute("CREATE INDEX IF NOT EXISTS orders_by_user_id_index ON orders (user_id)")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Add case for when new user joins the website and has no shares

    portfolio = user_portfolio("index")
    portfolio = dict(sorted(portfolio.items()))
    portfolioValue = 0

    # If the user has no portfolio yet this is a work-around to display an empty index page
    try:
        for symbol, shares in portfolio.items():
            ticker = lookup(symbol)
            name = ticker["name"]
            stockPrice = ticker["price"]
            stockValue = shares * stockPrice
            portfolioValue += stockValuestock 
            portfolio[symbol] = (name, shares, usd(stockPrice), usd(stockValue))

    except:
        portfolio = {}

    cash = db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]['cash']
    portfolioValue += cash

    return render_template("index.html", portfolio=portfolio, cash=usd(cash), portfolioValue=usd(portfolioValue))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Check if ticker exists
        ticker = request.form.get("ticker")
        shares = int(request.form.get("shares"))
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']

        if lookup(ticker) == None:
            return apology("symbol does not exist", 403)

        # Check if value of shares entered is greater than 0
        elif shares <= 0:
            return apology("Must buy more than 1 share", 403)

        # Check if user has enough cash
        tickerPrice = lookup(ticker)["price"]
        balance = cash - (shares * tickerPrice)

        if balance < 0:
            return apology("Insufficent funds to purchase shares", 403)

        # Update database with new balance and shares
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)
            db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", \
                                     user_id, ticker, shares, tickerPrice, datetime.now(timezone.utc))

        return redirect("/")


    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = user_portfolio("history")

    return render_template("history.html", transactions=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("ticker"):
            return apology("must provide a symbol", 403)

        # Ensure symbol is valid
        elif lookup(request.form.get("ticker")) == None:
            return apology("symbol does not exist", 403)

        # Grab info of symbol
        ticker = lookup(request.form.get("ticker"))

        return render_template("quote-success.html", name=ticker["symbol"], compName=ticker["name"], price=usd(ticker["price"]))

    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure no duplicate username
        elif db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username")):
            return apology("username already exists", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password was submitted
        elif not request.form.get("password-confirmation"):
            return apology("must confirm password", 403)

        # Ensure password and password-confirm are the same
        elif request.form.get("password") != request.form.get("password-confirmation"):
            return apology("passwords do not match", 403)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Log user in, i.e. Remember that this user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if  request.method == "POST":
        portfolio = user_portfolio("index")
        tickers = list(portfolio.keys())
        shares = int(request.form.get("shares"))
        ticker = request.form.get("symbol")

        # Checks if user has enough shares to sell, if not return an alert
        if portfolio[ticker] < shares:
            return render_template("sell.html", invalid=True, tickers=tickers, ticker=ticker)

        else:
            symbol = lookup(ticker)
            user_id = session["user_id"]
            cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
            marketPrice = symbol["price"]

            # Updates user cash balance
            newCash = cash + (marketPrice * shares)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, user_id)

            # Makes a record of the transaction
            db.execute("INSERT INTO orders (user_id, symbol, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)", \
                                    user_id, ticker, -shares, marketPrice, datetime.now(timezone.utc))

            return redirect("/")

    else:
        portfolio = user_portfolio("index")
        tickers = list(portfolio.keys())

        return render_template("sell.html", tickers=tickers)

def user_portfolio(route):
    """Helper function to pull users portfolio from database"""

    user_id = session["user_id"]
    portfolio = {}

    if route == "index":
        query = db.execute("SELECT symbol, SUM(shares) \
                            FROM orders \
                            WHERE user_id = ?", user_id)
        for row in query:
            symbol = row["symbol"]
            shares = row["SUM(shares)"]
            portfolio[symbol] = shares

        # for key in value in portfolio, if v != 0 then add that to the dict
        portfolio = {k: v for k, v in portfolio.items() if v != 0}

    elif route == "history":
        query = db.execute("SELECT symbol, shares, price, timestamp \
                            FROM orders \
                            WHERE user_id = ?", user_id)
        portfolio = query

    return portfolio
