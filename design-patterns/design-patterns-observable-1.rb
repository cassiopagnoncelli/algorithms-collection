module Email
  extend self

  def send(subject, sender, receiver)
    puts %Q[
      Subject: #{subject}
      From:    #{sender}@example.com
      To:      #{receiver}@example.com
      Date:    #{Time.now.asctime}
    ]
  end
end

class Alert
  def gotcha(person)
    puts "!!! ALERT: #{person.name.upcase} SENT AN EMAIL !!!"
  end
end

class Agent
  def gotcha(person)
    puts "!!! TIME TO DETAIN #{person.name.upcase} !!!"
  end
end

module Subject
  attr_reader :observers

  def initialize
    @observers = []
  end

  def add_observer(*observers)
    observers.each { |observer| @observers << observer }
  end

  def delete_observer(*observers)
    observers.each { |observer| @observers.delete(observer) }
  end

  def notify_observers
    observers.each { |observer| observer.gotcha(self) }
  end
end

class Person
  include Email, Subject

  attr_reader :name

  def initialize(name)
    super()                # Superclass (module) constructor --requires parenthesis
    @name = name
  end

  def send_email(subject, receiver)
    Email.send(subject, name, receiver)
    notify_observers
  end
end

alert = Alert.new
agent = Agent.new

bill = Person.new 'Bill'
bill.add_observer alert, agent         # Bill has now two observers watching him

bill.send_email 'Fishing trip', 'Fred'

