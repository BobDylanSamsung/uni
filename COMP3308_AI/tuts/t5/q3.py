vars = [["<=30", "high", False, "fair", False],
["<=30", "high", False, "excellent", False],
["31..40", "high", False, "fair", True],
[">40", "medium", False, "fair", True],
[">40", "low", True, "fair", True],
[">40", "low", True, "excellent", False],
["31..40", "low", True, "excellent", True],
["<=30", "medium", False, "fair", False],
["<=30", "low", True, "fair", True],
[">40", "medium", True, "fair", True],
["<=30", "medium", True, "excellent", True],
["31..40", "medium", False, "excellent", True],
["31..40", "high", True, "fair", True],
[">40", "medium", False, "excellent", False],]

x = ["<=30", 'medium', True, 'fair']
res = {"age":0, "income":0, "credit_rating": 0, "student": 0}
for attr in range(4):



