import pandas as pd
import joblib

from pathlib import Path
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report

# Project paths
PROJECT_ROOT = Path(__file__).resolve().parent.parent
DATA_PATH = PROJECT_ROOT / "data" / "sample_stress_data.csv"
MODEL_PATH = Path(__file__).resolve().parent / "stress_model.joblib"

# Load the demonstration dataset
df = pd.read_csv(DATA_PATH)

# Validate the dataset
required_columns = ["heart_rate", "temperature", "stress_level"]

if not all(column in df.columns for column in required_columns):
    raise ValueError(
        f"CSV must contain these columns: {required_columns}"
    )

if df[required_columns].isnull().any().any():
    raise ValueError("Dataset contains missing values.")

X = df[["heart_rate", "temperature"]]
y = df["stress_level"]

if y.nunique() < 2:
    raise ValueError("At least two stress-level classes are required.")

# Split the dataset
X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.25,
    random_state=42,
    stratify=y
)

# Train the model
model = RandomForestClassifier(
    n_estimators=100,
    random_state=42
)

model.fit(X_train, y_train)

# Evaluate the model
predictions = model.predict(X_test)

print("Model training completed!")
print(f"Demonstration accuracy: {accuracy_score(y_test, predictions):.2%}")

print("\nClassification report:")
print(
    classification_report(
        y_test,
        predictions,
        zero_division=0
    )
)

# Save the trained model
joblib.dump(model, MODEL_PATH)

print(f"\nModel saved successfully: {MODEL_PATH}")
print("Note: The dataset contains synthetic demonstration values.")
print("Results are not medically validated.")