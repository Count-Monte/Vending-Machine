NICKEL = 5
DIME = 10
QUARTER = 25
ONE = 100
FIVE = 500

store = [25, 25, 25, 0, 0]
price = [NICKEL, DIME, QUARTER, ONE, FIVE]
names = ["nickels", "dimes", "quarters", "ones", "fives"]

def print_deposit_menu():
    print("""
Menu for deposits:
  'n' - deposit a nickel
  'd' - deposit a dime
  'q' - deposit a quarter
  'o' - deposit a one dollar bill
  'f' - deposit a five dollar bill
  'c' - cancel the purchase
    """)

def print_store():
    print("Stock contains:")
    for i in range(5):
        print(f"  {store[i]} {names[i]}")
    print()

def calculate_best_refund(amount):
    print("\nPlease take the change below.")
    if not amount:
        print("  No change due.")
    
    id = 2
    while amount > 0 and id >= 0:
        cnt = amount // price[id]
        if cnt > store[id]:
            cnt = store[id]
        store[id] -= cnt
        amount -= cnt * price[id]
        
        if cnt:
            print(f"  {cnt} {names[id]}")
        id -= 1

    if id < 0 and amount > 0:
        print("Machine is out of change.")
        print("See store manager for remaining refund.")
        amount_due = []
        if amount >= 100:
            amount_due.append(f"{amount // 100} dollars")
        if amount % 100:
            amount_due.append(f"{amount % 100} cents")
        print(f"Amount due is: {' and '.join(amount_due)}")
    print()

def print_total_store():
    sum = 0
    for i in range(5):
        sum += store[i] * price[i]
    total = []
    if sum >= 100:
        total.append(f"{sum // 100} dollars")
    if sum % 100:
        total.append(f"{sum % 100} cents")
    print(f"\nTotal: {' and '.join(total)}")
    print()

def main():
    print("Welcome to the vending machine change maker program\nChange maker initialized.")
    print_store()
    
    while True:
        inputs = input("Enter the purchase price (xx.xx) or 'q' to quit: ")
        if inputs == 'q':
            break
        
        purchase = float(inputs)
        init_prc = cur_prc = int(purchase * 100)
        
        if cur_prc % 5:
            print("Illegal price: Must be a non-negative multiple of 5 cents.\n")
            continue
        
        print()
        print_deposit_menu()
        
        while True:
            payment_due = []
            if cur_prc >= 100:
                payment_due.append(f"{cur_prc // 100} dollars")
            if cur_prc % 100:
                payment_due.append(f"{cur_prc % 100} cents")
            print(f"Payment due: {' and '.join(payment_due)}")
            
            inputs = input("Indicate your deposit: ")
            
            if inputs == 'n':
                cur_prc -= NICKEL
                store[0] += 1
            elif inputs == 'd':
                cur_prc -= DIME
                store[1] += 1
            elif inputs == 'q':
                cur_prc -= QUARTER
                store[2] += 1
            elif inputs == 'o':
                cur_prc -= ONE
                store[3] += 1
            elif inputs == 'f':
                cur_prc -= FIVE
                store[4] += 1
            elif inputs == 'c':
                calculate_best_refund(init_prc - cur_prc)
                break
            else:
                print(f"Illegal selection: {inputs}")

            if cur_prc <= 0:
                cur_prc = -cur_prc
                calculate_best_refund(cur_prc)
                break

        print_store()

    print_total_store()

if __name__ == "__main__":
    main()
