import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from datetime import datetime
import warnings
warnings.filterwarnings('ignore')

# Set style for plots
plt.style.use('seaborn-v0_8-darkgrid')
sns.set_palette("husl")

def explore_kerala_data(file_path='data/kerala_rainfall.csv'):
    print("="*50)
    print("EXPLORING KERALA RAINFALL DATASET")
    print("="*50)
    
    # Load the dataset
    print("\n1. Loading data...")
    df = pd.read_csv(file_path)
    
    # Basic Information
    print("\n2. Dataset Shape:", df.shape)
    print("\n3. Columns:", df.columns.tolist())
    print("\n4. Data Types:")
    print(df.dtypes)
    
    print("\n5. First 5 rows:")
    print(df.head())
    
    print("\n6. Basic Statistics:")
    print(df.describe())
    
    print("\n7. Missing Values:")
    print(df.isnull().sum())
    
    # Check for Idukki district specifically
    print("\n8. Unique Districts:", df['DISTRICT'].unique())
    
    if 'DISTRICT' in df.columns:
        idukki_data = df[df['DISTRICT'] == 'IDUKKI']
        print(f"\n9. Idukki District Data Shape: {idukki_data.shape}")
        print(f"   Years covered: {idukki_data['YEAR'].min()} to {idukki_data['YEAR'].max()}")
        
        # Display Idukki data
        print("\n10. Idukki Rainfall (Sample):")
        print(idukki_data[['YEAR', 'JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN']].head())
    
    return df

def create_monthly_features(df):
    """Convert monthly columns to time series"""
    print("\n" + "="*50)
    print("CREATING TIME SERIES DATA")
    print("="*50)
    
    # Melt the dataframe (wide to long format)
    months = ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 
              'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC']
    
    # Create time series data
    time_series_data = []
    
    for index, row in df.iterrows():
        year = int(row['YEAR'])
        district = row.get('DISTRICT', 'KERALA')
        
        for i, month in enumerate(months, 1):
            # Create date
            date = datetime(year, i, 15)  # Mid-month date
            
            # Get rainfall value
            rainfall = row[month] if month in row else 0
            
            time_series_data.append({
                'date': date,
                'year': year,
                'month': i,
                'month_name': month,
                'district': district,
                'rainfall_mm': rainfall,
                'annual_total': row.get('ANNUAL', 0) if 'ANNUAL' in row else 0
            })
    
    # Create DataFrame
    ts_df = pd.DataFrame(time_series_data)
    
    print(f"\nCreated time series with {len(ts_df)} records")
    print(f"Time range: {ts_df['date'].min()} to {ts_df['date'].max()}")
    print(f"\nFirst 5 records:")
    print(ts_df.head())
    
    return ts_df

def visualize_data(df, district_name='IDUKKI'):
    """Create visualizations"""
    print("\n" + "="*50)
    print(f"VISUALIZING DATA FOR {district_name}")
    print("="*50)
    
    # Filter for specific district
    if 'district' in df.columns:
        district_df = df[df['district'] == district_name]
    else:
        district_df = df
    
    # Create figure
    fig, axes = plt.subplots(3, 2, figsize=(15, 12))
    fig.suptitle(f'Rainfall Analysis for {district_name}', fontsize=16, fontweight='bold')
    
    # 1. Annual Rainfall Trend
    ax1 = axes[0, 0]
    annual_data = district_df.groupby('year')['rainfall_mm'].sum().reset_index()
    ax1.plot(annual_data['year'], annual_data['rainfall_mm'], 
             marker='o', linewidth=2, markersize=4)
    ax1.set_title('Annual Rainfall Trend')
    ax1.set_xlabel('Year')
    ax1.set_ylabel('Rainfall (mm)')
    ax1.grid(True, alpha=0.3)
    
    # 2. Monthly Distribution (Boxplot)
    ax2 = axes[0, 1]
    monthly_agg = district_df.groupby('month_name')['rainfall_mm'].mean().reindex(
        ['JAN', 'FEB', 'MAR', 'APR', 'MAY', 'JUN', 
         'JUL', 'AUG', 'SEP', 'OCT', 'NOV', 'DEC']
    )
    monthly_agg.plot(kind='bar', ax=ax2, color='skyblue')
    ax2.set_title('Average Monthly Rainfall')
    ax2.set_xlabel('Month')
    ax2.set_ylabel('Average Rainfall (mm)')
    ax2.tick_params(axis='x', rotation=45)
    
    # 3. Monsoon vs Non-Monsoon
    ax3 = axes[1, 0]
    district_df['is_monsoon'] = district_df['month'].isin([6, 7, 8, 9])
    monsoon_data = district_df.groupby(['year', 'is_monsoon'])['rainfall_mm'].sum().unstack()
    monsoon_data.plot(kind='bar', stacked=True, ax=ax3, 
                      color=['lightcoral', 'lightgreen'])
    ax3.set_title('Monsoon vs Non-Monsoon Rainfall')
    ax3.set_xlabel('Year')
    ax3.set_ylabel('Rainfall (mm)')
    ax3.legend(['Non-Monsoon', 'Monsoon'])
    ax3.tick_params(axis='x', rotation=45)
    
    # 4. Rainfall Distribution
    ax4 = axes[1, 1]
    ax4.hist(district_df['rainfall_mm'], bins=50, 
             edgecolor='black', alpha=0.7, color='lightblue')
    ax4.axvline(district_df['rainfall_mm'].mean(), color='red', 
                linestyle='--', linewidth=2, label=f'Mean: {district_df["rainfall_mm"].mean():.1f}mm')
    ax4.axvline(district_df['rainfall_mm'].median(), color='green', 
                linestyle='--', linewidth=2, label=f'Median: {district_df["rainfall_mm"].median():.1f}mm')
    ax4.set_title('Rainfall Distribution')
    ax4.set_xlabel('Rainfall (mm)')
    ax4.set_ylabel('Frequency')
    ax4.legend()
    ax4.grid(True, alpha=0.3)
    
    # 5. Moving Average (7-month)
    ax5 = axes[2, 0]
    district_df_sorted = district_df.sort_values('date')
    district_df_sorted['7ma'] = district_df_sorted['rainfall_mm'].rolling(window=7).mean()
    ax5.plot(district_df_sorted['date'], district_df_sorted['rainfall_mm'], 
             alpha=0.5, label='Monthly', linewidth=1)
    ax5.plot(district_df_sorted['date'], district_df_sorted['7ma'], 
             color='red', linewidth=2, label='7-Month MA')
    ax5.set_title('Rainfall with 7-Month Moving Average')
    ax5.set_xlabel('Date')
    ax5.set_ylabel('Rainfall (mm)')
    ax5.legend()
    ax5.grid(True, alpha=0.3)
    
    # 6. Flood Events (Rainfall > 200mm)
    ax6 = axes[2, 1]
    flood_threshold = 200  # mm per month
    district_df['flood_event'] = (district_df['rainfall_mm'] > flood_threshold).astype(int)
    flood_events = district_df[district_df['flood_event'] == 1]
    ax6.scatter(flood_events['date'], flood_events['rainfall_mm'], 
                color='red', s=50, alpha=0.7, label=f'Flood Events (> {flood_threshold}mm)')
    ax6.axhline(y=flood_threshold, color='orange', linestyle='--', 
                linewidth=2, label=f'Threshold: {flood_threshold}mm')
    ax6.set_title('Flood Events Detection')
    ax6.set_xlabel('Date')
    ax6.set_ylabel('Rainfall (mm)')
    ax6.legend()
    ax6.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('data/rainfall_analysis.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # Print flood statistics
    print(f"\nFlood Event Statistics (Threshold: {flood_threshold}mm):")
    print(f"Total months analyzed: {len(district_df)}")
    print(f"Flood events detected: {district_df['flood_event'].sum()}")
    print(f"Percentage of flood months: {district_df['flood_event'].mean()*100:.2f}%")
    
    # Show flood events by year
    flood_by_year = district_df.groupby('year')['flood_event'].sum()
    print(f"\nFlood Events by Year:")
    print(flood_by_year[flood_by_year > 0])
    
    return district_df

def save_processed_data(df, output_path='data/processed_kerala_rainfall.csv'):
    """Save processed data for modeling"""
    df.to_csv(output_path, index=False)
    print(f"\nProcessed data saved to: {output_path}")
    print(f"File size: {os.path.getsize(output_path) / 1024 / 1024:.2f} MB")
    
    return output_path

if _name_ == '_main_':
    # Step 1: Load and explore
    df = explore_kerala_data('data/kerala_rainfall.csv')
    
    # Step 2: Create time series
    ts_df = create_monthly_features(df)
    
    # Step 3: Visualize (focus on Idukki if available)
    if 'district' in ts_df.columns:
        # Check if Idukki data exists
        if 'IDUKKI' in ts_df['district'].unique():
            idukki_df = visualize_data(ts_df, 'IDUKKI')
        else:
            print("\nIdukki district not found in data. Using all Kerala data.")
            all_df = visualize_data(ts_df, 'KERALA')
    else:
        all_df = visualize_data(ts_df)
    
    # Step 4: Save processed data
    save_processed_data(ts_df)
