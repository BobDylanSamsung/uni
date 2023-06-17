from pet import pet
import unittest

class PetTest(unittest.TestCase):
    def test_has_nickname(self):
        lucy = pet("lucy", 2, "dog", False)
        lucy.add_nickname("bitch")
        self.assertTrue(lucy.has_nickname("bitch"))
        self.assertTrue(not(lucy.has_nickname("luigi")))

    def test_add_nickname(self):
        lucy = pet("lucy", 2, "dog", False)

        self.assertEqual(lucy.add_nickname("bitch"), "success")

        self.assertEqual(lucy.add_nickname("bitch"), "fail")
