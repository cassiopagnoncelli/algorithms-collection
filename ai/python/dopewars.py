from random import random, shuffle, randint
from json import dumps
from os import system
from operator import itemgetter
from math import sqrt, log, exp
import locale

# Set formatting standard for thousands separator.
locale.setlocale(locale.LC_ALL, 'en_US')

class Drug(object):
  def __init__(self, name, price_range, especially_cheap=False, especially_expensive=False):
    self.name = name
    self.lower = min(price_range)
    self.upper = max(price_range)
    self.especially_cheap = especially_cheap
    self.especially_expensive = especially_expensive
  def current_price(self):
    x = random()
    # Price on especially cheap conditions.
    if self.especially_cheap and x < 0.1:
      return 0.3*self.lower + 0.7*self.lower*random()
    # Price on especially expensive conditions.
    elif self.especially_expensive and x > 0.90:
      return self.upper + 2.5*self.upper*random()
    # Price on normal conditions.
    return self.lower + x * (self.upper - self.lower)
  def relative_price(self, price):
    return (price - self.lower) / float(self.upper - self.lower)

class Game(object):
  def __init__(self, rounds=30):
    self.rounds = rounds
    self.current_round = 0
  def round(self):
    # Check for end of the game.
    if self.current_round >= self.rounds:
      return False
    self.current_round += 1
    # Sampling without replacement.
    global drugs_list
    selected = drugs_list.keys()
    if self.current_round < self.rounds:
      shuffle(selected)
      selected = selected[ : randint(5, len(drugs_list)) + 1]
    # Return.
    return dict([ tuple([drug, drugs_list[drug].current_price()]) for drug in selected ])

class Player(object):
  def __init__(self, game, reporting=False, initial_debt=5500, debt_interest=0.1, balance=2000, capacity=100):
    self.game = game
    self.reporting = reporting
    self.debt = initial_debt
    self.debt_interest = debt_interest
    self.balance = balance
    self.capacity = capacity
    global drugs_list
    self.portfolio = dict(zip(drugs_list.keys(), [0] * len(drugs_list)))
    self.round = False
  def start_game(self, interactive=True, sell_thres=0.3, buy_thres=0.3, qty_afordability_thres=150):
    self.round = self.game.round()
    while self.round:
      if interactive:
        self.interactive_play()
      else:
        self.ai_play(sell_thres, buy_thres, qty_afordability_thres)
      # Update interest.
      self.debt += self.debt * self.debt_interest
      # Iteration.
      self.round = self.game.round()
    # Clear drugs and calculate final balance.
    if interactive:
      system("clear")
      print "Balance: %s   Debt: %s   Slots: %d / %d   Round: %d / %d" % (
        locale.format("%d", int(self.balance), grouping=True),
        locale.format("%d", int(self.debt), grouping=True),
        sum(self.portfolio.values()),
        self.capacity,
        self.game.current_round,
        self.game.rounds)
    if self.reporting:
      if sum(self.portfolio.values()) > 0:
        print "Drugs outstanding in portfolio:"
        print dumps(dict(filter(lambda x: x[1] > 0, self.portfolio.items())), sort_keys=True, indent=3)
      print "Final balance: %s - %s = %s" % (
        locale.format("%d", int(self.balance), grouping=True),
        locale.format("%d", int(self.debt), grouping=True),
        locale.format("%d", int(self.balance - self.debt), grouping=True))
    return self.balance - self.debt
  def buy(self, drug, qty='MAX'):
    max_qty_space = self.capacity - sum(self.portfolio.values())
    max_qty_money = int(self.balance / self.round[drug])
    max_qty = min(max_qty_space, max_qty_money)
    if qty == 'MAX':
      qty = max_qty
    if qty > 0 and qty <= max_qty:
      self.portfolio[drug] += qty
      self.balance -= self.round[drug] * qty
      if self.reporting:
        print "round %d: +%d %s" % (self.game.current_round, qty, drug)
      return qty
    return 0
  def sell(self, drug, qty='ALL'):
    max_qty = self.portfolio[drug]
    if qty == 'ALL':
      qty = max_qty
    if qty > 0 and qty <= max_qty:
      self.portfolio[drug] -= qty
      self.balance += self.round[drug] * qty
      if self.reporting:
        print "round %d: -%d %s" % (self.game.current_round, qty, drug)
      return qty
    return 0
  def terminal(self):
    system("clear")
    print "Balance: %s   Debt: %s   Slots: %d / %d   Round: %d / %d" % (
      locale.format("%d", int(self.balance), grouping=True),
      locale.format("%d", int(self.debt), grouping=True),
      sum(self.portfolio.values()),
      self.capacity,
      self.game.current_round,
      self.game.rounds)
    print "{"
    for d in sorted(self.round.items(), key=itemgetter(1))[::-1]:
      print "%10s %10.0f" % (d[0], d[1])
    print "}"
  def get_cmd(self):
    print ">",
    cmd = raw_input().strip().split()
    if len(cmd) == 0:
      return False
    if len(cmd) == 1 and cmd[0] in ['?', 'help']:
      print "Command: b|s drug [qty]"
    elif len(cmd) in [2, 3] and cmd[0] in ['B', 'b']:
      qty = 'MAX' if len(cmd) == 2 else int(cmd[2])
      drug_name = cmd[1].lower()
      if self.round.has_key(drug_name):
        self.terminal()
        print "+%d x %s    Current balance: %s" % (
          self.buy(drug_name, qty),
          drug_name,
          locale.format("%d", int(self.balance), grouping=True))
      else:
        print "This drug doesn't exists, dude!"
    elif len(cmd) in [2, 3] and cmd[0] in ['S', 's']:
      qty = 'ALL' if len(cmd) == 2 else int(cmd[2])
      drug_name = cmd[1].lower()
      if self.round.has_key(drug_name):
        self.terminal()
        print "- %d x %s    Current balance: %s" % (
          self.sell(drug_name, qty),
          drug_name,
          locale.format("%d", int(self.balance), grouping=True))
      else:
        print "This drug doesn't exists, dude!"
    elif len(cmd) == 1 and cmd[0] in ['Q', 'q']:
      exit()
    return 1
  def interactive_play(self):
    self.terminal()
    while self.get_cmd():
      pass
  def ai_play(self, sell_thres, buy_thres, qty_afordability_thres):
    # Items in portfolio.
    portfolio_items = map(lambda x: x[0], filter(lambda y: y[1] > 0, self.portfolio.items()))
    # Operational portfolio, op_portfolio, are currently marketable items held in portfolio.
    #marketable_portfolio = [ x for x in portfolio_items if x in self.round.keys() ]
    # Market (relative) prices.
    rel_prices = dict([ tuple([d[0], drugs_list[d[0]].relative_price(d[1])]) for d in self.round.items() ])
    # Maximum amounts afordable.
    max_amounts = { x: self.balance / self.round[x] for x in self.round.keys() }
    ##
    ## Portfolio rebalancing.
    ##
    # Prospective sales.
    sell_candidates = map(lambda x: x[0], filter(lambda y: y[1] > sell_thres, rel_prices.items()))
    for i in sell_candidates:
      self.sell(i)
    if self.game.current_round == self.game.rounds:
      for i in portfolio_items:
        self.sell(i)
    # Buy.
    buy_candidates = map(lambda x: x[0], filter(lambda y: 
      y[1] < buy_thres and max_amounts[y[0]] > 0 and max_amounts[y[0]] < qty_afordability_thres, rel_prices.items()))
    order_criteria = sorted({ x[0]: x[1] for x in max_amounts.items() if x[0] in buy_candidates }.items(), key=itemgetter(1))
    if self.game.rounds - self.game.current_round > 1:
      for i in order_criteria:
        self.buy(i[0])

drugs_list = {
    "acid": Drug("acid", xrange(1000, 4000), "The market is flooded with cheap home-made acid!", False),
    "cocaine": Drug("cocaine", xrange(15000, 29000), False, "Cops made a big cocaine bust! Prices are outrageous!"),
    "hashish": Drug("hashish", xrange(480, 1280), "The Marrakesh Express has arrived!", False),
    "heroin": Drug("heroin", xrange(5500, 13000), False, "Addicts are buying heroin at ridiculous prices!"),
    "ludes": Drug("ludes", xrange(11, 60), "Rival drug dealers raided a pharmacy and are selling cheap ludes!", False),
    "opium": Drug("opium", xrange(540, 1250), False, "Addicts are buying opium at unreasonable prices!"),
    "shrooms": Drug("shrooms", xrange(500, 1300), "Maaaario!", False),
    "speed": Drug("speed", xrange(90, 400), False, "End of semester, run for speed!"),
    "weed": Drug("weed", xrange(315, 890), "Columbian freighter dusted the Coast Guard! Weed prices have bottomed out!", False),
    "mda": Drug("mda", xrange(1500, 4500), False, False),
    "pcp": Drug("peyote", xrange(1000, 2500), False, False),
    "peyote": Drug("peyote", xrange(300, 1000), False, False)
  }

# Optimization: find the best parameters.
# max_val, best_sell, best_buy, best_qty = 0, 0, 0, 0
# for sell_point in map(lambda x: x/100.0, range(30, 70, 5)):
#   for buy_point in map(lambda x: x/100.0, range(10, 50, 5)):
#     for qty_point in range(100, 250, 50):
#       vals = [ Player(Game()).start_game(False, sell_point, buy_point, qty_point) for k in xrange(30) ]
#       #vals = map(lambda y: log(y), filter(lambda x: x > 1, vals))
#       vals = map(lambda y: log(y) if y > 1 else -1, vals)
#       current_val = sum(vals) / len(vals)
#       if current_val > max_val:
#         max_val = current_val
#         best_sell, best_buy, best_qty = sell_point, buy_point, qty_point
# print "Best average balance %s found with params" % locale.format("%d", int(exp(current_val)), grouping=True)
# print "sell=%.2f   buy=%.2f   qty=%d" % (best_sell, best_buy, best_qty)

Player(Game(), True).start_game(True)
