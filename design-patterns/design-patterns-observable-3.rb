# require the observer lib file
require 'observer'

class Notifier
end
 
class EmailNotifier < Notifier
  def update(bank_account)
    if bank_account.balance <= 10
      puts "Sending email to: #{bank_account.owner} informing his account balance: $#{bank_account.balance}."
      # send the email mechanism
    end
  end
end
 
class SMSNotifier < Notifier
  def update(bank_account)
    if bank_account.balance <= 5
      puts "Sending SMS to: #{bank_account.owner} informing his account balance: $#{bank_account.balance}."
      # send sms mechanism
    end
  end
end
 
class BankAccount
  # include the observable module
  include Observable 
  attr_reader :owner, :balance

  def initialize(owner,amount)
    @owner,@balance = owner,amount
    # adding list of observes to the account
    add_observer EmailNotifier.new  
    add_observer SMSNotifier.new
  end
  
  # withdraw operation
  def withdraw(amount)
    # do whatever you need
    @balance -=amount if (@balance - amount) > 0
    # now here comes our logic
    # issue that the account has changed
    changed
    # notify the observers
    notify_observers self
  end
end

account = BankAccount.new 'Jim Oslen', 100
account.withdraw 60
account.withdraw 30.5
account.withdraw 6
