#http://ruby-doc.org/stdlib-1.9.3/libdoc/observer/rdoc/Observable.html

require 'observer'

class Ticker             # Periodically fetch a stock price.
  include Observable

  def initialize(symbol)
    @symbol = symbol
  end

  def run
    last_price = nil
    loop do
      price = Price.fetch(@symbol)
      print "Current price: #{price}\n"
      if price != last_price
        changed                              # notify observers
        last_price = price
        notify_observers(Time.now, price)
      end
      sleep 2
    end
  end
end

class Price
  def Price.fetch(symbol)
    60 + rand(80)
  end
end

class Warner
  def initialize(ticker, limit)
    @limit = limit
    ticker.add_observer(self)
  end
end

class WarnLow < Warner
  def update(time, price)          # callback for observer
    puts "--- #{time.to_s}: Price below #@limit: #{price}" if price < @limit
  end
end

class WarnHigh < Warner
  def update(time, price)          # callback for observer
    puts "+++ #{time.to_s}: Price above #@limit: #{price}" if price > @limit
  end
end

ticker = Ticker.new "MSFT"     # Ticker in an observable object.
WarnLow.new ticker, 80         # WarnLow is a Ticker's observer.
WarnHigh.new ticker, 120       # WarnHigh is also a Ticker's observer.
ticker.run                     # Start the game.
